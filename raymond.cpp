#include "raymond.h"
#include "stdafx.h"

#include "src/World/World.h"
#include <thread>
#include <algorithm>
#include <random>
#include <chrono>
#include "commctrl.h"
#include <sstream>


// utility functions:
QImage* CreateCheckered(int width, int height) {

    QImage* bmp = new QImage(width, height, QImage::Format_Indexed8);

    QColor light(180, 180, 180);
    QColor dark(120, 120, 120);

    for (UINT i = 0; i < width; i++)
        for (UINT ii = 0; ii < height; ii++) {
            if ((i % 16 >= 8) ^ (ii % 16 >= 8))
                bmp->setPixelColor(i, ii, light);
            else
                bmp->setPixelColor(i, ii, dark);
        }

    return bmp;
}

std::vector<std::vector<pix_coord>> DistributePixels(const int num_threads, const int chunk_size, const int width, const int height) {

    pix_coord* indices = new pix_coord[width * height];

    struct chunk {
        int ul_x, ul_y, lr_x, lr_y, num_pixels_in_chunk;
    };

    int hor_num_chunks = width / chunk_size;
    if (width % chunk_size > 0)
        hor_num_chunks++;

    int ver_num_chunks = height / chunk_size;
    if (height % chunk_size > 0)
        ver_num_chunks++;

    int num_chunks = hor_num_chunks * ver_num_chunks;

    chunk* chunk_arr = new chunk[num_chunks];

    for (int ch = 0; ch < num_chunks; ch++) {

        chunk_arr[ch].ul_x = (ch % hor_num_chunks) * chunk_size;

        chunk_arr[ch].ul_y = ch / hor_num_chunks * chunk_size;

        if ((chunk_arr[ch].ul_x + chunk_size) > width)
            chunk_arr[ch].lr_x = width - 1;
        else
            chunk_arr[ch].lr_x = chunk_arr[ch].ul_x + chunk_size - 1;

        if ((chunk_arr[ch].ul_y + chunk_size) > height)
            chunk_arr[ch].lr_y = height - 1;
        else
            chunk_arr[ch].lr_y = chunk_arr[ch].ul_y + chunk_size - 1;
    }

    //shuffle chunks:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(chunk_arr, chunk_arr + num_chunks, std::default_random_engine(seed));


    //split into batches:
    std::vector<std::vector<pix_coord>> batches;
    for (int i = 0; i < num_threads; i++)
        batches.push_back(std::vector<pix_coord>());

    int curr_index = 0;

    for (int ch = 0; ch < num_chunks; ch++) {

        int hor_chunk_size = chunk_arr[ch].lr_x - chunk_arr[ch].ul_x + 1;
        int ver_chunk_size = chunk_arr[ch].lr_y - chunk_arr[ch].ul_y + 1;
        int num_pixels = hor_chunk_size * ver_chunk_size;

        std::vector<pix_coord> temp;

        for (int i = 0; i < num_pixels; i++) {
            pix_coord chunk_pixel;
            chunk_pixel.x = chunk_arr[ch].ul_x + (i % hor_chunk_size);
            chunk_pixel.y = chunk_arr[ch].ul_y + (i / hor_chunk_size);

            temp.push_back(chunk_pixel);
        }

        //shuffle pixels:
        int size = temp.size();
        for (int ii = 0; ii < size - 1; ii++) {
            int j = ii + rand() % (size - ii);
            swap(temp[ii], temp[j]);
        }

        for (int i = 0; i < size; i++) {
            batches[ch % num_threads].push_back(temp[i]);
        }
    }

    return batches;
}

//Thread:
Thread::Thread(World* _world, Raymond* _main_window) : world(_world), main_window(_main_window), pixels(std::vector<RenderPixel*>()) {
    //world->paintArea = this;
}

void
Thread::SetPixel(const int x, const int y, const int r, const int g, const int b) {

    RenderPixel* pixel_ptr = new RenderPixel(x, y, r, g, b);
    pixels.push_back(pixel_ptr);

    if (pixels.size() > 9) //replace with timer check
        NotifyCanvas();
}

void
Thread::NotifyCanvas() {

    std::vector<RenderPixel*>* pixelsUpdate = new std::vector<RenderPixel*>(pixels);
    pixels.clear();

    this->main_window->update_pixels(pixelsUpdate);
}

void
Thread::Render(std::vector<pix_coord> batch, Thread* thread) {
    world->camera_ptr->render_scene(*world, batch, thread);
}

Raymond::Raymond(QWidget* parent)
    : QWidget(parent),
    image_label(new QLabel),
    scroll_area(new QScrollArea)
{
    ui.setupUi(this);

    QVBoxLayout* box_layout = new QVBoxLayout(this);

    this->create_actions();
    this->create_menus();

    this->image_label->setBackgroundRole(QPalette::Base);
    this->image_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    this->image_label->setScaledContents(true);

    this->scroll_area->setBackgroundRole(QPalette::Dark);
    this->scroll_area->setWidget(this->image_label);
    this->scroll_area->setVisible(false);
    //setCentralWidget(this->scroll_area);

    this->canvas = CreateCheckered(this->world->vp.hres, this->world->vp.vres);
}

void Raymond::create_actions()
{
    this->save_as_action = new QAction("Save As", this);
    connect(this->save_as_action, &QAction::triggered, this, &Raymond::save_as);

    this->exit_action = new QAction("Exit", this);
    connect(this->exit_action, &QAction::triggered, this, &Raymond::exit);

    this->render_start_action = new QAction("Start", this);
    connect(this->render_start_action, &QAction::triggered, this, &Raymond::render_start);
}

void Raymond::create_menus()
{
    QMenuBar* menu_bar = new QMenuBar();

    QMenu* file_menu = new QMenu("File");
    menu_bar->addMenu(file_menu);
    file_menu->addAction(this->save_as_action);
    file_menu->addAction(this->exit_action);

    QMenu* render_menu = new QMenu("Render");
    menu_bar->addMenu(render_menu);
    render_menu->addAction(this->render_start_action);

    this->layout()->setMenuBar(menu_bar);
}

void Raymond::update_pixels(std::vector<RenderPixel*>* new_pixels) 
{
    std::vector<RenderPixel*> update_pixels(*new_pixels);
    delete new_pixels;
    for (int i = 0; i < update_pixels.size(); i++) {
        RenderPixel* p = update_pixels[i];
        this->canvas->setPixelColor(p->x, p->y, QColor(p->r, p->g, p->b));
        this->repaint();
    }
}

void Raymond::save_as() {}
void Raymond::exit() {}
void Raymond::render_start() {}

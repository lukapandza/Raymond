#include "raymond.h"
#include "stdafx.h"
#include "src/World/World.h"
#include <thread>
#include <algorithm>
#include <random>
#include "commctrl.h"
#include <sstream>
#include <string>


// utility functions:
QImage CreateCheckered(int width, int height) {

    QImage bmp(width, height, QImage::Format_RGB32);

    QColor light(180, 180, 180);
    QColor dark(120, 120, 120);

    for (UINT i = 0; i < width; i++)
        for (UINT ii = 0; ii < height; ii++) {
            if ((i % 16 >= 8) ^ (ii % 16 >= 8))
                bmp.setPixelColor(i, ii, light);
            else
                bmp.setPixelColor(i, ii, dark);
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

std::string time_string_from_int(int total_seconds) {
    
    std::string out = "";

    int elapsed_seconds = total_seconds % 60;
    int elapsed_minutes = total_seconds / 60;
    int elapsed_hours = elapsed_minutes / 60;

    out += (elapsed_hours < 10 ? "0" : "") + std::to_string(elapsed_hours) + ":";
    out += (elapsed_minutes < 10 ? "0" : "") + std::to_string(elapsed_minutes) + ":";
    out += (elapsed_seconds < 10 ? "0" : "") + std::to_string(elapsed_seconds);

    return out;
}

//Thread:
Thread::Thread(World* _world, Raymond* _main_window, int _thread_id) : world(_world), main_window(_main_window), thread_id(_thread_id), pixel_buffer(std::vector<RenderPixel*>()) {}

void
Thread::SetPixel(const int x, const int y, const int r, const int g, const int b) {
    
    /*
    while (this->main_window->is_repainting)
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

    this->pixel_buffer.push_back(new RenderPixel(x, y, r, g, b));
    */
    this->main_window->mtx.lock();
    this->main_window->canvas.setPixelColor(x, y, QColor(r, g, b));
    this->main_window->pixels_rendered++;
    this->main_window->mtx.unlock();
}

void
Thread::Render(std::vector<pix_coord> batch, Thread* thread) {
    world->camera_ptr->render_scene(*world, batch, thread);
    //this->main_window->rendering_status[this->thread_id] = false;
}

Raymond::Raymond()
    : QMainWindow(),
    image_label(new QLabel),
    status_label(new QLabel),
    progress_bar(new QProgressBar)
{
    //ui.setupUi(this);

    QVBoxLayout* box_layout = new QVBoxLayout;
    QWidget* central_widget = new QWidget;

    this->create_actions();
    this->create_menus();

    this->image_label->setBackgroundRole(QPalette::Base);
    this->image_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->image_label->setAlignment(Qt::AlignCenter);
    this->image_label->setScaledContents(true);
    this->image_label->setVisible(false);

    this->setCentralWidget(central_widget);
    central_widget->setLayout(box_layout);
    box_layout->addWidget(this->image_label);

    this->statusBar()->addPermanentWidget(this->progress_bar);
    this->progress_bar->setValue(0);
    this->progress_bar->setVisible(false);

    this->statusBar()->addWidget(this->status_label);
    this->status_label->setText(QString("Ready."));

    
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

void Raymond::paint_from_buffers() 
{
    /*
    this->is_repainting = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(1)); 
    // to give time for any last pixel to be written to the buffer in threads
    // 1 ms seems to be lowest wait time that consistently produces no lost pixels at the worst
    // possible conditions I could configure (very fast rendering cases)

    for (int i = 0; i < this->threads.size(); i++) {
        int size = this->threads[i]->pixel_buffer.size();
        for (int ii = 0; ii < size; ii++) {
            this->canvas.setPixelColor(
                this->threads[i]->pixel_buffer[ii]->x,
                this->threads[i]->pixel_buffer[ii]->y,
                QColor(
                    this->threads[i]->pixel_buffer[ii]->r,
                    this->threads[i]->pixel_buffer[ii]->g,
                    this->threads[i]->pixel_buffer[ii]->b));

            this->pixels_rendered++;
        }
        this->threads[i]->pixel_buffer.clear();
    }

    this->is_repainting = false;

    this->image_label->setPixmap(QPixmap::fromImage(this->canvas));
    this->image_label->repaint();
    */

    mtx.lock();
    this->image_label->setPixmap(QPixmap::fromImage(this->canvas));
    this->image_label->repaint();
    mtx.unlock();
}

// slots:
void Raymond::save_as() {
    QString file_name = QFileDialog::getSaveFileName(this, tr("Save File"), "./Renders/untitled.png", tr("Image (*.png)"));
    this->canvas.save(file_name, nullptr, 100); //max quality
}

void Raymond::exit() {
    QApplication::quit();
}

void Raymond::render_start() 
{
    this->world = new World();
    this->world->build();

    this->pixels_to_render = this->world->vp.hres * this->world->vp.vres;

    this->canvas = CreateCheckered(this->world->vp.hres, this->world->vp.vres);
    this->image_label->setPixmap(QPixmap::fromImage(this->canvas));
    this->image_label->adjustSize();
    this->image_label->setVisible(true);
    this->image_label->repaint();
    this->image_label->show();
    this->resize(this->image_label->size());
    this->repaint();

    const int num_threads = std::max(std::thread::hardware_concurrency(), uint(1));
    //const int num_threads = 1;
    std::vector<std::vector<pix_coord>> batches = DistributePixels(num_threads, 32, world->vp.hres, world->vp.vres);

    this->is_rendering = true;

    this->timer = new QTimer(this);
    connect(this->timer, &QTimer::timeout, this, QOverload<>::of(&Raymond::update_image));
    this->timer->start(this->repaint_frequency); // update displayed image every time interval

    
    this->status_timer = new QTimer(this);
    connect(this->status_timer, &QTimer::timeout, this, QOverload<>::of(&Raymond::update_status_message));
    this->status_timer->start(1000); // update message every second

    this->start_time = std::chrono::steady_clock::now();
    this->progress_bar->setVisible(true);

    for (int i = 0; i < num_threads; i++) {

        World* thread_world = new World();
        thread_world->build();

        Thread* new_thread = new Thread(thread_world, this, i);

        this->threads.push_back(new_thread);
        //this->rendering_status.push_back(true);

        std::thread thread(&Thread::Render, *this->threads[i], batches[i], this->threads[i]);
        thread.detach();
    }
}

void Raymond::update_image()
{
    /*
    if (this->is_rendering)
        this->paint_from_buffers();

    this->is_rendering = false;

    for (int i = 0; i < this->rendering_status.size(); i++) {
        if (this->rendering_status[i]) {
            this->is_rendering = true;
            break;
        }
    }

    if (!this->is_rendering) { 
        // sometimes a few pixels get caught in the buffers during the repaint function
        // at the end of render, but before the check of thread status is complete.
        // this is a last scoop of render buffers for such cases. 
        this->paint_from_buffers();
    }
    */
    this->mtx.lock();
    this->image_label->setPixmap(QPixmap::fromImage(this->canvas));
    this->image_label->repaint();
    this->mtx.unlock();
}

void Raymond::update_status_message() 
{
    if (this->pixels_rendered == this->pixels_to_render)
        this->render_end();
    else {
    
        std::string message = "";
        message += "Rendering... ";
        auto curr_time = std::chrono::steady_clock::now();
        int total_elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(curr_time - this->start_time).count();

        message += time_string_from_int(total_elapsed_seconds);

        int speed = this->pixels_rendered / (total_elapsed_seconds + 1); // to avoid div by 0

        message += " [ " + std::to_string(speed) + " pixels / second ] Time Remaining: ";

        message += time_string_from_int((this->pixels_to_render - this->pixels_rendered) / speed);

        this->status_label->setText(QString::fromStdString(message));

        this->progress_bar->setValue((int)(this->pixels_rendered * 100.0 / this->pixels_to_render));
    }
}

void Raymond::render_end()
{
    delete this->status_timer;

    std::string message = "";
    message += "Done. Elapsed time: ";

    auto curr_time = std::chrono::steady_clock::now();
    int total_elapsed_seconds = std::chrono::duration_cast<std::chrono::seconds>(curr_time - this->start_time).count();
    
    message += time_string_from_int(total_elapsed_seconds);

    this->status_label->setText(QString::fromStdString(message));
    this->progress_bar->setValue(100);
}

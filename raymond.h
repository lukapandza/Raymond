#pragma once

#include <QtWidgets/QWidget>
#include <QLabel>
#include <qstatusbar.h>
#include "ui_raymond.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <mutex>

// forward declerations:
class World;
class Thread;

struct RenderPixel
{
public:
    RenderPixel(int _x, int _y, int _r, int _g, int _b) : x(_x), y(_y), r(_r), g(_g), b(_b) {}

public:
    int x, y;
    int r, g, b;
};

struct pix_coord {
    int x, y;
};

class Raymond : public QWidget
{
    Q_OBJECT

public:
    Raymond(QWidget* parent = nullptr);

    Ui::RaymondClass ui;

    World* world;
    std::vector<Thread*> threads;
    std::vector<bool> rendering_status;
    bool is_rendering = false;
    bool is_repainting = false;
    QTimer* timer;
    int repaint_frequency = 16; // 60 fps = 16.66 ms.
    std::mutex mtx;

    QImage canvas;
    QLabel* image_label;
    double scale_factor = 1.0;

    QAction* save_as_action;
    QAction* exit_action;
    QAction* render_start_action;

    int pixels_to_render;
    int pixels_rendered = 0;

    std::chrono::time_point<std::chrono::steady_clock> start_time;

    QLabel* status_label;
    QStatusBar* status_bar;
    QTimer* status_timer;

    void create_actions();
    void create_menus();
    void paint_from_buffers();

private slots:
    void save_as();
    void exit();
    void render_start();
    void update_image();
    void update_status_message();
};

class Thread{

public:

    World* world;
    int thread_id;
    std::vector<RenderPixel*> pixel_buffer;
    Raymond* main_window;

    Thread(World* _world, Raymond* _main_window, int _thread_id);

    void SetPixel(const int x, const int y, const int r, const int g, const int b);

    void Render(std::vector<pix_coord> batch, Thread* thread);
};

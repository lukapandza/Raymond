#pragma once

#include <qmainwindow.h>
#include <QtWidgets/QWidget>
#include <QLabel>
#include <qstatusbar.h>
#include "ui_raymond.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <mutex>
#include <qprogressbar.h>

// forward declerations:
class World;
class Thread;

struct pix_coord {
    int x, y;
};

class Raymond : public QMainWindow
{
    Q_OBJECT

public:
    Raymond();

    Ui::RaymondClass ui;

    World* world;
    std::vector<Thread*> threads;

    QTimer* timer;
    int repaint_frequency = 1000; // 60 fps = 16.66 ms.
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
    QProgressBar* progress_bar;
    QTimer* status_timer;

    void create_actions();
    void create_menus();

private slots:
    void save_as();
    void exit();
    void render_start();
    void update_image();
    void update_status_message();
    void render_end();
};

class Thread{

public:

    World* world;
    int thread_id;
    Raymond* main_window;

    Thread(World* _world, Raymond* _main_window, int _thread_id);

    void SetPixel(const int x, const int y, const int r, const int g, const int b);

    void Render(std::vector<pix_coord> batch, Thread* thread);
};

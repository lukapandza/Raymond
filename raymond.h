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
#include "src/Utilities/QueuedPixel.h"
#include "src/Utilities/AdaptiveThread.h"
#include <queue>
#include <unordered_map>

// forward declerations:
class World;
class Thread;

struct pix_coord 
{
    int x, y;

    pix_coord() : x(0), y(0) {};

    pix_coord(int _x, int _y) : x(_x), y(_y) {};

    bool operator== (const pix_coord& rhs) const { return this->x == rhs.x && this->y == rhs.y; }
};

struct hash_func 
{
    std::size_t operator() (const pix_coord& p) const
    {
        std::size_t h1 = std::hash<int>()(p.x);
        std::size_t h2 = std::hash<int>()(p.y);

        return h1 ^ h2;
    }
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
    int repaint_frequency = 16; // 60 fps = 16.66 ms.
    int status_update_frequency = 250; // .25s
    std::mutex mtx;

    bool adaptive = false;
    std::priority_queue<QueuedPixel*, std::vector<QueuedPixel*>, ComparePointers> queue;

    QAction* show_image_action;

    std::unordered_map<pix_coord, int, hash_func> sample_density_map;
    QImage* sample_canvas = nullptr;
    QAction* show_sample_map_action;

    std::unordered_map<pix_coord, double, hash_func> variance_density_map;
    QImage* variance_canvas = nullptr;
    QAction* show_variance_map_action;

    QImage* displayed_canvas = nullptr;

    QImage canvas;
    QLabel* image_label;
    double scale_factor = 1.0;

    QAction* save_as_action;
    QAction* exit_action;
    QAction* render_start_action;
    QAction* adaptive_render_start_action;
    unsigned long long samples_skipped = 0;

    unsigned long long pixels_to_render;
    unsigned long long pixels_rendered = 0;
    int last_pixels_rendered = 0;

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
    void adaptive_render_start();
    void update_image();
    void update_status_message();
    void render_end();

    void show_image();
    
    void generate_sample_map();
    void show_sample_map();

    void generate_variance_map();
    void show_variance_map();
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

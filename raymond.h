#pragma once

#include <QtWidgets/QWidget>
#include <QLabel>
#include <QScrollArea>
#include "ui_raymond.h"
#include <vector>
#include <iostream>

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
    std::vector<RenderPixel*> pixels;
    std::vector<Thread*> threads;
    std::vector<bool> rendering_status;
    bool is_rendering = false;
    QTimer* timer;
    int repaint_frequency = 100;

    QImage canvas;
    QLabel* image_label;
    //QScrollArea* scroll_area;
    double scale_factor = 1.0;

    QAction* save_as_action;
    QAction* exit_action;
    QAction* render_start_action;

    void create_actions();
    void create_menus();

signals:
    void new_pixels(std::vector<RenderPixel*>* new_pixels);

private slots:
    void save_as();
    void exit();
    void render_start();
    void update_image();
};

class Thread{

public:

    World* world;
    int thread_id;
    std::vector<RenderPixel*> pixels;
    Raymond* main_window;

    Thread(World* _world, Raymond* _main_window, int _thread_id);

    void SetPixel(const int x, const int y, const int r, const int g, const int b);

    void NotifyCanvas();

    void Render(std::vector<pix_coord> batch, Thread* thread);
};

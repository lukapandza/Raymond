#pragma once

#include <QtWidgets/QWidget>
#include <Qlabel.h>
#include <QScrollArea>
#include "ui_raymond.h"
#include <vector>

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
    Raymond(QWidget* parent = Q_NULLPTR);

    Ui::RaymondClass ui;

    World* world;
    std::vector<RenderPixel*> pixels;

    QImage* canvas;
    QLabel* image_label;
    QScrollArea* scroll_area;
    double scale_factor = 1.0;

    QAction* save_as_action;
    QAction* exit_action;
    QAction* render_start_action;

    void create_actions();
    void create_menus();

    void update_pixels(std::vector<RenderPixel*>* new_pixels);

private slots:
    void save_as();
    void exit();
    void render_start();
};

class Thread {

public:

    World* world;
    Raymond* main_window;
    std::vector<RenderPixel*> pixels;

    Thread(World* _world, Raymond* _main_window);

    void SetPixel(const int x, const int y, const int r, const int g, const int b);

    void NotifyCanvas();

    void Render(std::vector<pix_coord> batch, Thread* thread);
};

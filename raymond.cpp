#include "raymond.h"
#include "stdafx.h"

Raymond::Raymond(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    QVBoxLayout* box_layout = new QVBoxLayout(this);

    QMenuBar* menu_bar = new QMenuBar();

    QMenu* file_menu = new QMenu("File");
    menu_bar->addMenu(file_menu);
    file_menu->addAction("Save As");
    file_menu->addAction("Exit");

    QMenu* render_menu = new QMenu("Render");
    menu_bar->addMenu(render_menu);
    render_menu->addAction("Start");

    this->layout()->setMenuBar(menu_bar);
}

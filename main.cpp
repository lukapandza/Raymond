#include "raymond.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Raymond w;
    w.show();
    return a.exec();
}

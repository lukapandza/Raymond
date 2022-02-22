#pragma once

#include <QtWidgets/QWidget>
#include "ui_raymond.h"

class Raymond : public QWidget
{
    Q_OBJECT

public:
    Raymond(QWidget *parent = Q_NULLPTR);

private:
    Ui::RaymondClass ui;
};

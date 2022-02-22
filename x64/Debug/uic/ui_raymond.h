/********************************************************************************
** Form generated from reading UI file 'raymond.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RAYMOND_H
#define UI_RAYMOND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RaymondClass
{
public:

    void setupUi(QWidget *RaymondClass)
    {
        if (RaymondClass->objectName().isEmpty())
            RaymondClass->setObjectName(QString::fromUtf8("RaymondClass"));
        RaymondClass->resize(600, 400);

        retranslateUi(RaymondClass);

        QMetaObject::connectSlotsByName(RaymondClass);
    } // setupUi

    void retranslateUi(QWidget *RaymondClass)
    {
        RaymondClass->setWindowTitle(QApplication::translate("RaymondClass", "Raymond", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RaymondClass: public Ui_RaymondClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RAYMOND_H

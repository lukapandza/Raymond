/****************************************************************************
** Meta object code from reading C++ file 'raymond.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../../raymond.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'raymond.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Raymond_t {
    QByteArrayData data[14];
    char stringdata0[190];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Raymond_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Raymond_t qt_meta_stringdata_Raymond = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Raymond"
QT_MOC_LITERAL(1, 8, 7), // "save_as"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 4), // "exit"
QT_MOC_LITERAL(4, 22, 12), // "render_start"
QT_MOC_LITERAL(5, 35, 21), // "adaptive_render_start"
QT_MOC_LITERAL(6, 57, 12), // "update_image"
QT_MOC_LITERAL(7, 70, 21), // "update_status_message"
QT_MOC_LITERAL(8, 92, 10), // "render_end"
QT_MOC_LITERAL(9, 103, 10), // "show_image"
QT_MOC_LITERAL(10, 114, 19), // "generate_sample_map"
QT_MOC_LITERAL(11, 134, 15), // "show_sample_map"
QT_MOC_LITERAL(12, 150, 21), // "generate_variance_map"
QT_MOC_LITERAL(13, 172, 17) // "show_variance_map"

    },
    "Raymond\0save_as\0\0exit\0render_start\0"
    "adaptive_render_start\0update_image\0"
    "update_status_message\0render_end\0"
    "show_image\0generate_sample_map\0"
    "show_sample_map\0generate_variance_map\0"
    "show_variance_map"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Raymond[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Raymond::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Raymond *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->save_as(); break;
        case 1: _t->exit(); break;
        case 2: _t->render_start(); break;
        case 3: _t->adaptive_render_start(); break;
        case 4: _t->update_image(); break;
        case 5: _t->update_status_message(); break;
        case 6: _t->render_end(); break;
        case 7: _t->show_image(); break;
        case 8: _t->generate_sample_map(); break;
        case 9: _t->show_sample_map(); break;
        case 10: _t->generate_variance_map(); break;
        case 11: _t->show_variance_map(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Raymond::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_Raymond.data,
    qt_meta_data_Raymond,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Raymond::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Raymond::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Raymond.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Raymond::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

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
    QByteArrayData data[8];
    char stringdata0[86];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Raymond_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Raymond_t qt_meta_stringdata_Raymond = {
    {
QT_MOC_LITERAL(0, 0, 7), // "Raymond"
QT_MOC_LITERAL(1, 8, 10), // "new_pixels"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 26), // "std::vector<RenderPixel*>*"
QT_MOC_LITERAL(4, 47, 7), // "save_as"
QT_MOC_LITERAL(5, 55, 4), // "exit"
QT_MOC_LITERAL(6, 60, 12), // "render_start"
QT_MOC_LITERAL(7, 73, 12) // "update_image"

    },
    "Raymond\0new_pixels\0\0std::vector<RenderPixel*>*\0"
    "save_as\0exit\0render_start\0update_image"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Raymond[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   42,    2, 0x08 /* Private */,
       5,    0,   43,    2, 0x08 /* Private */,
       6,    0,   44,    2, 0x08 /* Private */,
       7,    0,   45,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    1,

 // slots: parameters
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
        case 0: _t->new_pixels((*reinterpret_cast< std::vector<RenderPixel*>*(*)>(_a[1]))); break;
        case 1: _t->save_as(); break;
        case 2: _t->exit(); break;
        case 3: _t->render_start(); break;
        case 4: _t->update_image(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Raymond::*)(std::vector<RenderPixel*> * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Raymond::new_pixels)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Raymond::staticMetaObject = { {
    &QWidget::staticMetaObject,
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
    return QWidget::qt_metacast(_clname);
}

int Raymond::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void Raymond::new_pixels(std::vector<RenderPixel*> * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

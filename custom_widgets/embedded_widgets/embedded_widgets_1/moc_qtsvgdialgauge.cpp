/****************************************************************************
** Meta object code from reading C++ file 'qtsvgdialgauge.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qt_embedded_widgets/src/svgdialgauge/qtsvgdialgauge.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtsvgdialgauge.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QtSvgDialGauge_t {
    QByteArrayData data[9];
    char stringdata[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QtSvgDialGauge_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QtSvgDialGauge_t qt_meta_stringdata_QtSvgDialGauge = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 8),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 5),
QT_MOC_LITERAL(4, 31, 4),
QT_MOC_LITERAL(5, 36, 7),
QT_MOC_LITERAL(6, 44, 7),
QT_MOC_LITERAL(7, 52, 10),
QT_MOC_LITERAL(8, 63, 8)
    },
    "QtSvgDialGauge\0setValue\0\0value\0skin\0"
    "minimum\0maximum\0startAngle\0endAngle\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtSvgDialGauge[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       5,   22, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // properties: name, type, flags
       4, QMetaType::QString, 0x00095103,
       5, QMetaType::Int, 0x00095103,
       6, QMetaType::Int, 0x00095103,
       7, QMetaType::QReal, 0x00095103,
       8, QMetaType::QReal, 0x00095103,

       0        // eod
};

void QtSvgDialGauge::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtSvgDialGauge *_t = static_cast<QtSvgDialGauge *>(_o);
        switch (_id) {
        case 0: _t->setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QtSvgDialGauge::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QtSvgDialGauge.data,
      qt_meta_data_QtSvgDialGauge,  qt_static_metacall, 0, 0}
};


const QMetaObject *QtSvgDialGauge::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtSvgDialGauge::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtSvgDialGauge.stringdata))
        return static_cast<void*>(const_cast< QtSvgDialGauge*>(this));
    return QWidget::qt_metacast(_clname);
}

int QtSvgDialGauge::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = skin(); break;
        case 1: *reinterpret_cast< int*>(_v) = minimum(); break;
        case 2: *reinterpret_cast< int*>(_v) = maximum(); break;
        case 3: *reinterpret_cast< qreal*>(_v) = startAngle(); break;
        case 4: *reinterpret_cast< qreal*>(_v) = endAngle(); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setSkin(*reinterpret_cast< QString*>(_v)); break;
        case 1: setMinimum(*reinterpret_cast< int*>(_v)); break;
        case 2: setMaximum(*reinterpret_cast< int*>(_v)); break;
        case 3: setStartAngle(*reinterpret_cast< qreal*>(_v)); break;
        case 4: setEndAngle(*reinterpret_cast< qreal*>(_v)); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_END_MOC_NAMESPACE

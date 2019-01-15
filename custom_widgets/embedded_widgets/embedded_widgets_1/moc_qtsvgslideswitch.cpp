/****************************************************************************
** Meta object code from reading C++ file 'qtsvgslideswitch.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qt_embedded_widgets/src/svgslideswitch/qtsvgslideswitch.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtsvgslideswitch.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtSvgSlideSwitch_t {
    QByteArrayData data[7];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtSvgSlideSwitch_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtSvgSlideSwitch_t qt_meta_stringdata_QtSvgSlideSwitch = {
    {
QT_MOC_LITERAL(0, 0, 16), // "QtSvgSlideSwitch"
QT_MOC_LITERAL(1, 17, 17), // "setSwitchPosition"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 8), // "position"
QT_MOC_LITERAL(4, 45, 20), // "updateSwitchPosition"
QT_MOC_LITERAL(5, 66, 7), // "checked"
QT_MOC_LITERAL(6, 74, 4) // "skin"

    },
    "QtSvgSlideSwitch\0setSwitchPosition\0\0"
    "position\0updateSwitchPosition\0checked\0"
    "skin"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtSvgSlideSwitch[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       1,   30, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x08 /* Private */,
       4,    1,   27,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,    5,

 // properties: name, type, flags
       6, QMetaType::QString, 0x00095103,

       0        // eod
};

void QtSvgSlideSwitch::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtSvgSlideSwitch *_t = static_cast<QtSvgSlideSwitch *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setSwitchPosition((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updateSwitchPosition((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        QtSvgSlideSwitch *_t = static_cast<QtSvgSlideSwitch *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->skin(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        QtSvgSlideSwitch *_t = static_cast<QtSvgSlideSwitch *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setSkin(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject QtSvgSlideSwitch::staticMetaObject = {
    { &QAbstractButton::staticMetaObject, qt_meta_stringdata_QtSvgSlideSwitch.data,
      qt_meta_data_QtSvgSlideSwitch,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QtSvgSlideSwitch::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtSvgSlideSwitch::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtSvgSlideSwitch.stringdata0))
        return static_cast<void*>(this);
    return QAbstractButton::qt_metacast(_clname);
}

int QtSvgSlideSwitch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

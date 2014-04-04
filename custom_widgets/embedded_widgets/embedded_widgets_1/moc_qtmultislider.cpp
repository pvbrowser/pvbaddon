/****************************************************************************
** Meta object code from reading C++ file 'qtmultislider.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qt_embedded_widgets/src/multislider/qtmultislider.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtmultislider.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QtMultiSliderHelper_t {
    QByteArrayData data[1];
    char stringdata[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QtMultiSliderHelper_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QtMultiSliderHelper_t qt_meta_stringdata_QtMultiSliderHelper = {
    {
QT_MOC_LITERAL(0, 0, 19)
    },
    "QtMultiSliderHelper\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtMultiSliderHelper[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void QtMultiSliderHelper::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject QtMultiSliderHelper::staticMetaObject = {
    { &QAbstractSlider::staticMetaObject, qt_meta_stringdata_QtMultiSliderHelper.data,
      qt_meta_data_QtMultiSliderHelper,  qt_static_metacall, 0, 0}
};


const QMetaObject *QtMultiSliderHelper::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtMultiSliderHelper::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtMultiSliderHelper.stringdata))
        return static_cast<void*>(const_cast< QtMultiSliderHelper*>(this));
    return QAbstractSlider::qt_metacast(_clname);
}

int QtMultiSliderHelper::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractSlider::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_QtMultiSlider_t {
    QByteArrayData data[14];
    char stringdata[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_QtMultiSlider_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_QtMultiSlider_t qt_meta_stringdata_QtMultiSlider = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 15),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 8),
QT_MOC_LITERAL(4, 40, 15),
QT_MOC_LITERAL(5, 56, 15),
QT_MOC_LITERAL(6, 72, 7),
QT_MOC_LITERAL(7, 80, 15),
QT_MOC_LITERAL(8, 96, 7),
QT_MOC_LITERAL(9, 104, 8),
QT_MOC_LITERAL(10, 113, 17),
QT_MOC_LITERAL(11, 131, 5),
QT_MOC_LITERAL(12, 137, 17),
QT_MOC_LITERAL(13, 155, 4)
    },
    "QtMultiSlider\0maximumExceeded\0\0exceeded\0"
    "minimumExceeded\0setMaximumRange\0maximum\0"
    "setMinimumRange\0minimum\0setValue\0"
    "checkMinimumRange\0value\0checkMaximumRange\0"
    "skin\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtMultiSlider[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       1,   70, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x05,
       4,    1,   52,    2, 0x05,

 // slots: name, argc, parameters, tag, flags
       5,    1,   55,    2, 0x0a,
       7,    1,   58,    2, 0x0a,
       9,    1,   61,    2, 0x0a,
      10,    1,   64,    2, 0x08,
      12,    1,   67,    2, 0x08,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::Int,   11,

 // properties: name, type, flags
      13, QMetaType::QString, 0x00095103,

       0        // eod
};

void QtMultiSlider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtMultiSlider *_t = static_cast<QtMultiSlider *>(_o);
        switch (_id) {
        case 0: _t->maximumExceeded((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->minimumExceeded((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->setMaximumRange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setMinimumRange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->checkMinimumRange((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->checkMaximumRange((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QtMultiSlider::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QtMultiSlider::maximumExceeded)) {
                *result = 0;
            }
        }
        {
            typedef void (QtMultiSlider::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QtMultiSlider::minimumExceeded)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject QtMultiSlider::staticMetaObject = {
    { &QProgressBar::staticMetaObject, qt_meta_stringdata_QtMultiSlider.data,
      qt_meta_data_QtMultiSlider,  qt_static_metacall, 0, 0}
};


const QMetaObject *QtMultiSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtMultiSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QtMultiSlider.stringdata))
        return static_cast<void*>(const_cast< QtMultiSlider*>(this));
    return QProgressBar::qt_metacast(_clname);
}

int QtMultiSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QProgressBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = skin(); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: setSkin(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 1;
    } else if (_c == QMetaObject::ResetProperty) {
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
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void QtMultiSlider::maximumExceeded(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QtMultiSlider::minimumExceeded(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE

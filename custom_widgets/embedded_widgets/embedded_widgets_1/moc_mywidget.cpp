/****************************************************************************
** Meta object code from reading C++ file 'mywidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mywidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mywidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_myButton_t {
    QByteArrayData data[3];
    char stringdata0[22];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myButton_t qt_meta_stringdata_myButton = {
    {
QT_MOC_LITERAL(0, 0, 8), // "myButton"
QT_MOC_LITERAL(1, 9, 11), // "slotClicked"
QT_MOC_LITERAL(2, 21, 0) // ""

    },
    "myButton\0slotClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void myButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myButton *_t = static_cast<myButton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject myButton::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_myButton.data,
      qt_meta_data_myButton,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *myButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myButton.stringdata0))
        return static_cast<void*>(this);
    return QPushButton::qt_metacast(_clname);
}

int myButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
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
    return _id;
}
struct qt_meta_stringdata_myQtSvgDialGauge_t {
    QByteArrayData data[2];
    char stringdata0[23];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myQtSvgDialGauge_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myQtSvgDialGauge_t qt_meta_stringdata_myQtSvgDialGauge = {
    {
QT_MOC_LITERAL(0, 0, 16), // "myQtSvgDialGauge"
QT_MOC_LITERAL(1, 17, 5) // "value"

    },
    "myQtSvgDialGauge\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myQtSvgDialGauge[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       1,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::Int, 0x00095103,

       0        // eod
};

void myQtSvgDialGauge::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        myQtSvgDialGauge *_t = static_cast<myQtSvgDialGauge *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->value(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        myQtSvgDialGauge *_t = static_cast<myQtSvgDialGauge *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setValue(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject myQtSvgDialGauge::staticMetaObject = {
    { &QtSvgDialGauge::staticMetaObject, qt_meta_stringdata_myQtSvgDialGauge.data,
      qt_meta_data_myQtSvgDialGauge,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *myQtSvgDialGauge::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myQtSvgDialGauge::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myQtSvgDialGauge.stringdata0))
        return static_cast<void*>(this);
    return QtSvgDialGauge::qt_metacast(_clname);
}

int myQtSvgDialGauge::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtSvgDialGauge::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
   if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
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
struct qt_meta_stringdata_myQt5WayButton_t {
    QByteArrayData data[7];
    char stringdata0[52];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myQt5WayButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myQt5WayButton_t qt_meta_stringdata_myQt5WayButton = {
    {
QT_MOC_LITERAL(0, 0, 14), // "myQt5WayButton"
QT_MOC_LITERAL(1, 15, 4), // "onUp"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 6), // "onDown"
QT_MOC_LITERAL(4, 28, 6), // "onLeft"
QT_MOC_LITERAL(5, 35, 7), // "onRight"
QT_MOC_LITERAL(6, 43, 8) // "onCenter"

    },
    "myQt5WayButton\0onUp\0\0onDown\0onLeft\0"
    "onRight\0onCenter"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myQt5WayButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    0,   42,    2, 0x0a /* Public */,
       6,    0,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void myQt5WayButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myQt5WayButton *_t = static_cast<myQt5WayButton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onUp(); break;
        case 1: _t->onDown(); break;
        case 2: _t->onLeft(); break;
        case 3: _t->onRight(); break;
        case 4: _t->onCenter(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject myQt5WayButton::staticMetaObject = {
    { &Qt5WayButton::staticMetaObject, qt_meta_stringdata_myQt5WayButton.data,
      qt_meta_data_myQt5WayButton,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *myQt5WayButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myQt5WayButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myQt5WayButton.stringdata0))
        return static_cast<void*>(this);
    return Qt5WayButton::qt_metacast(_clname);
}

int myQt5WayButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Qt5WayButton::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_myQtBasicDialGauge_t {
    QByteArrayData data[4];
    char stringdata0[41];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myQtBasicDialGauge_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myQtBasicDialGauge_t qt_meta_stringdata_myQtBasicDialGauge = {
    {
QT_MOC_LITERAL(0, 0, 18), // "myQtBasicDialGauge"
QT_MOC_LITERAL(1, 19, 7), // "minimum"
QT_MOC_LITERAL(2, 27, 7), // "maximum"
QT_MOC_LITERAL(3, 35, 5) // "value"

    },
    "myQtBasicDialGauge\0minimum\0maximum\0"
    "value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myQtBasicDialGauge[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       3,   14, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // properties: name, type, flags
       1, QMetaType::Int, 0x00095103,
       2, QMetaType::Int, 0x00095103,
       3, QMetaType::Int, 0x00095103,

       0        // eod
};

void myQtBasicDialGauge::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{

#ifndef QT_NO_PROPERTIES
    if (_c == QMetaObject::ReadProperty) {
        myQtBasicDialGauge *_t = static_cast<myQtBasicDialGauge *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->minimum(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->maximum(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->value(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        myQtBasicDialGauge *_t = static_cast<myQtBasicDialGauge *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setMinimum(*reinterpret_cast< int*>(_v)); break;
        case 1: _t->setMaximum(*reinterpret_cast< int*>(_v)); break;
        case 2: _t->setValue(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject myQtBasicDialGauge::staticMetaObject = {
    { &QtBasicDialGauge::staticMetaObject, qt_meta_stringdata_myQtBasicDialGauge.data,
      qt_meta_data_myQtBasicDialGauge,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *myQtBasicDialGauge::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myQtBasicDialGauge::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myQtBasicDialGauge.stringdata0))
        return static_cast<void*>(this);
    return QtBasicDialGauge::qt_metacast(_clname);
}

int myQtBasicDialGauge::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtBasicDialGauge::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    
#ifndef QT_NO_PROPERTIES
   if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 3;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 3;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
struct qt_meta_stringdata_myQtMultiSlider_t {
    QByteArrayData data[6];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myQtMultiSlider_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myQtMultiSlider_t qt_meta_stringdata_myQtMultiSlider = {
    {
QT_MOC_LITERAL(0, 0, 15), // "myQtMultiSlider"
QT_MOC_LITERAL(1, 16, 12), // "onTopChanged"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 6), // "newval"
QT_MOC_LITERAL(4, 37, 15), // "onBottomChanged"
QT_MOC_LITERAL(5, 53, 5) // "value"

    },
    "myQtMultiSlider\0onTopChanged\0\0newval\0"
    "onBottomChanged\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myQtMultiSlider[] = {

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
       1,    1,   24,    2, 0x0a /* Public */,
       4,    1,   27,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // properties: name, type, flags
       5, QMetaType::Int, 0x00095103,

       0        // eod
};

void myQtMultiSlider::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myQtMultiSlider *_t = static_cast<myQtMultiSlider *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onTopChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onBottomChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        myQtMultiSlider *_t = static_cast<myQtMultiSlider *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->value(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        myQtMultiSlider *_t = static_cast<myQtMultiSlider *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setValue(*reinterpret_cast< int*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject myQtMultiSlider::staticMetaObject = {
    { &QtMultiSlider::staticMetaObject, qt_meta_stringdata_myQtMultiSlider.data,
      qt_meta_data_myQtMultiSlider,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *myQtMultiSlider::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myQtMultiSlider::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myQtMultiSlider.stringdata0))
        return static_cast<void*>(this);
    return QtMultiSlider::qt_metacast(_clname);
}

int myQtMultiSlider::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtMultiSlider::qt_metacall(_c, _id, _a);
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
struct qt_meta_stringdata_myQtScrollDial_t {
    QByteArrayData data[4];
    char stringdata0[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myQtScrollDial_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myQtScrollDial_t qt_meta_stringdata_myQtScrollDial = {
    {
QT_MOC_LITERAL(0, 0, 14), // "myQtScrollDial"
QT_MOC_LITERAL(1, 15, 14), // "onValueChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 6) // "newval"

    },
    "myQtScrollDial\0onValueChanged\0\0newval"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myQtScrollDial[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void myQtScrollDial::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myQtScrollDial *_t = static_cast<myQtScrollDial *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject myQtScrollDial::staticMetaObject = {
    { &QtScrollDial::staticMetaObject, qt_meta_stringdata_myQtScrollDial.data,
      qt_meta_data_myQtScrollDial,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *myQtScrollDial::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myQtScrollDial::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myQtScrollDial.stringdata0))
        return static_cast<void*>(this);
    return QtScrollDial::qt_metacast(_clname);
}

int myQtScrollDial::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtScrollDial::qt_metacall(_c, _id, _a);
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
    return _id;
}
struct qt_meta_stringdata_myQtScrollWheel_t {
    QByteArrayData data[4];
    char stringdata0[39];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myQtScrollWheel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myQtScrollWheel_t qt_meta_stringdata_myQtScrollWheel = {
    {
QT_MOC_LITERAL(0, 0, 15), // "myQtScrollWheel"
QT_MOC_LITERAL(1, 16, 14), // "onValueChanged"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 6) // "newval"

    },
    "myQtScrollWheel\0onValueChanged\0\0newval"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myQtScrollWheel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void myQtScrollWheel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myQtScrollWheel *_t = static_cast<myQtScrollWheel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject myQtScrollWheel::staticMetaObject = {
    { &QtScrollWheel::staticMetaObject, qt_meta_stringdata_myQtScrollWheel.data,
      qt_meta_data_myQtScrollWheel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *myQtScrollWheel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myQtScrollWheel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myQtScrollWheel.stringdata0))
        return static_cast<void*>(this);
    return QtScrollWheel::qt_metacast(_clname);
}

int myQtScrollWheel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtScrollWheel::qt_metacall(_c, _id, _a);
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
    return _id;
}
struct qt_meta_stringdata_myQtSvgButton_t {
    QByteArrayData data[3];
    char stringdata0[25];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myQtSvgButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myQtSvgButton_t qt_meta_stringdata_myQtSvgButton = {
    {
QT_MOC_LITERAL(0, 0, 13), // "myQtSvgButton"
QT_MOC_LITERAL(1, 14, 9), // "onClicked"
QT_MOC_LITERAL(2, 24, 0) // ""

    },
    "myQtSvgButton\0onClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myQtSvgButton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void myQtSvgButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myQtSvgButton *_t = static_cast<myQtSvgButton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject myQtSvgButton::staticMetaObject = {
    { &QtSvgButton::staticMetaObject, qt_meta_stringdata_myQtSvgButton.data,
      qt_meta_data_myQtSvgButton,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *myQtSvgButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myQtSvgButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myQtSvgButton.stringdata0))
        return static_cast<void*>(this);
    return QtSvgButton::qt_metacast(_clname);
}

int myQtSvgButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtSvgButton::qt_metacall(_c, _id, _a);
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
    return _id;
}
struct qt_meta_stringdata_myQtSvgSlideSwitch_t {
    QByteArrayData data[4];
    char stringdata0[38];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myQtSvgSlideSwitch_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myQtSvgSlideSwitch_t qt_meta_stringdata_myQtSvgSlideSwitch = {
    {
QT_MOC_LITERAL(0, 0, 18), // "myQtSvgSlideSwitch"
QT_MOC_LITERAL(1, 19, 9), // "onToggled"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 7) // "checked"

    },
    "myQtSvgSlideSwitch\0onToggled\0\0checked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myQtSvgSlideSwitch[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void myQtSvgSlideSwitch::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myQtSvgSlideSwitch *_t = static_cast<myQtSvgSlideSwitch *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject myQtSvgSlideSwitch::staticMetaObject = {
    { &QtSvgSlideSwitch::staticMetaObject, qt_meta_stringdata_myQtSvgSlideSwitch.data,
      qt_meta_data_myQtSvgSlideSwitch,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *myQtSvgSlideSwitch::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myQtSvgSlideSwitch::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myQtSvgSlideSwitch.stringdata0))
        return static_cast<void*>(this);
    return QtSvgSlideSwitch::qt_metacast(_clname);
}

int myQtSvgSlideSwitch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtSvgSlideSwitch::qt_metacall(_c, _id, _a);
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
    return _id;
}
struct qt_meta_stringdata_myQtSvgToggleSwitch_t {
    QByteArrayData data[4];
    char stringdata0[39];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myQtSvgToggleSwitch_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myQtSvgToggleSwitch_t qt_meta_stringdata_myQtSvgToggleSwitch = {
    {
QT_MOC_LITERAL(0, 0, 19), // "myQtSvgToggleSwitch"
QT_MOC_LITERAL(1, 20, 9), // "onToggled"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 7) // "checked"

    },
    "myQtSvgToggleSwitch\0onToggled\0\0checked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myQtSvgToggleSwitch[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void myQtSvgToggleSwitch::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myQtSvgToggleSwitch *_t = static_cast<myQtSvgToggleSwitch *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onToggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject myQtSvgToggleSwitch::staticMetaObject = {
    { &QtSvgToggleSwitch::staticMetaObject, qt_meta_stringdata_myQtSvgToggleSwitch.data,
      qt_meta_data_myQtSvgToggleSwitch,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *myQtSvgToggleSwitch::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myQtSvgToggleSwitch::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myQtSvgToggleSwitch.stringdata0))
        return static_cast<void*>(this);
    return QtSvgToggleSwitch::qt_metacast(_clname);
}

int myQtSvgToggleSwitch::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtSvgToggleSwitch::qt_metacall(_c, _id, _a);
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
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

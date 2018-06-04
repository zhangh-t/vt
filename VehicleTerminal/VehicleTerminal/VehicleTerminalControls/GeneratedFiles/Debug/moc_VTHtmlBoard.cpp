/****************************************************************************
** Meta object code from reading C++ file 'VTHtmlBoard.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/VTHtmlBoard.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VTHtmlBoard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VTHtmlBoard_t {
    QByteArrayData data[4];
    char stringdata[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_VTHtmlBoard_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_VTHtmlBoard_t qt_meta_stringdata_VTHtmlBoard = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 8),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 26)
    },
    "VTHtmlBoard\0onLoaded\0\0onJavascriptObjectsCleared\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VTHtmlBoard[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x08,
       3,    0,   27,    2, 0x08,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,

       0        // eod
};

void VTHtmlBoard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VTHtmlBoard *_t = static_cast<VTHtmlBoard *>(_o);
        switch (_id) {
        case 0: _t->onLoaded((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->onJavascriptObjectsCleared(); break;
        default: ;
        }
    }
}

const QMetaObject VTHtmlBoard::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VTHtmlBoard.data,
      qt_meta_data_VTHtmlBoard,  qt_static_metacall, 0, 0}
};


const QMetaObject *VTHtmlBoard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VTHtmlBoard::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VTHtmlBoard.stringdata))
        return static_cast<void*>(const_cast< VTHtmlBoard*>(this));
    return QWidget::qt_metacast(_clname);
}

int VTHtmlBoard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
    return _id;
}
struct qt_meta_stringdata_VTHtmlBoardReadyNotifier_t {
    QByteArrayData data[6];
    char stringdata[66];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_VTHtmlBoardReadyNotifier_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_VTHtmlBoardReadyNotifier_t qt_meta_stringdata_VTHtmlBoardReadyNotifier = {
    {
QT_MOC_LITERAL(0, 0, 24),
QT_MOC_LITERAL(1, 25, 5),
QT_MOC_LITERAL(2, 31, 0),
QT_MOC_LITERAL(3, 32, 17),
QT_MOC_LITERAL(4, 50, 6),
QT_MOC_LITERAL(5, 57, 7)
    },
    "VTHtmlBoardReadyNotifier\0ready\0\0"
    "actualSizeChanged\0nWidth\0nHeight\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VTHtmlBoardReadyNotifier[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x0a,
       3,    2,   25,    2, 0x0a,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    5,

       0        // eod
};

void VTHtmlBoardReadyNotifier::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VTHtmlBoardReadyNotifier *_t = static_cast<VTHtmlBoardReadyNotifier *>(_o);
        switch (_id) {
        case 0: _t->ready(); break;
        case 1: _t->actualSizeChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject VTHtmlBoardReadyNotifier::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VTHtmlBoardReadyNotifier.data,
      qt_meta_data_VTHtmlBoardReadyNotifier,  qt_static_metacall, 0, 0}
};


const QMetaObject *VTHtmlBoardReadyNotifier::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VTHtmlBoardReadyNotifier::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_VTHtmlBoardReadyNotifier.stringdata))
        return static_cast<void*>(const_cast< VTHtmlBoardReadyNotifier*>(this));
    return QObject::qt_metacast(_clname);
}

int VTHtmlBoardReadyNotifier::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
    return _id;
}
QT_END_MOC_NAMESPACE

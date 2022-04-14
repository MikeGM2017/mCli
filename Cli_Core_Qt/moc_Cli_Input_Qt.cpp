/****************************************************************************
** Meta object code from reading C++ file 'Cli_Input_Qt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Cli_Input/Cli_Input_Qt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Cli_Input_Qt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Cli_Input_Qt_Wait_Thread_t {
    QByteArrayData data[3];
    char stringdata[52];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Cli_Input_Qt_Wait_Thread_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Cli_Input_Qt_Wait_Thread_t qt_meta_stringdata_Cli_Input_Qt_Wait_Thread = {
    {
QT_MOC_LITERAL(0, 0, 24), // "Cli_Input_Qt_Wait_Thread"
QT_MOC_LITERAL(1, 25, 25), // "Wait_Count_Changed_Signal"
QT_MOC_LITERAL(2, 51, 0) // ""

    },
    "Cli_Input_Qt_Wait_Thread\0"
    "Wait_Count_Changed_Signal\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Cli_Input_Qt_Wait_Thread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void Cli_Input_Qt_Wait_Thread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Cli_Input_Qt_Wait_Thread *_t = static_cast<Cli_Input_Qt_Wait_Thread *>(_o);
        switch (_id) {
        case 0: _t->Wait_Count_Changed_Signal((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Cli_Input_Qt_Wait_Thread::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Cli_Input_Qt_Wait_Thread::Wait_Count_Changed_Signal)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject Cli_Input_Qt_Wait_Thread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_Cli_Input_Qt_Wait_Thread.data,
      qt_meta_data_Cli_Input_Qt_Wait_Thread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Cli_Input_Qt_Wait_Thread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Cli_Input_Qt_Wait_Thread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Cli_Input_Qt_Wait_Thread.stringdata))
        return static_cast<void*>(const_cast< Cli_Input_Qt_Wait_Thread*>(this));
    return QThread::qt_metacast(_clname);
}

int Cli_Input_Qt_Wait_Thread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void Cli_Input_Qt_Wait_Thread::Wait_Count_Changed_Signal(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_Cli_Input_Qt_t {
    QByteArrayData data[4];
    char stringdata[40];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Cli_Input_Qt_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Cli_Input_Qt_t qt_meta_stringdata_Cli_Input_Qt = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Cli_Input_Qt"
QT_MOC_LITERAL(1, 13, 23), // "Wait_Count_Changed_Slot"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 1) // "v"

    },
    "Cli_Input_Qt\0Wait_Count_Changed_Slot\0"
    "\0v"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Cli_Input_Qt[] = {

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

void Cli_Input_Qt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Cli_Input_Qt *_t = static_cast<Cli_Input_Qt *>(_o);
        switch (_id) {
        case 0: _t->Wait_Count_Changed_Slot((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Cli_Input_Qt::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Cli_Input_Qt.data,
      qt_meta_data_Cli_Input_Qt,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Cli_Input_Qt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Cli_Input_Qt::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Cli_Input_Qt.stringdata))
        return static_cast<void*>(const_cast< Cli_Input_Qt*>(this));
    if (!strcmp(_clname, "Cli_Input_Abstract"))
        return static_cast< Cli_Input_Abstract*>(const_cast< Cli_Input_Qt*>(this));
    return QObject::qt_metacast(_clname);
}

int Cli_Input_Qt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE

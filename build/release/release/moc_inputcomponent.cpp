/****************************************************************************
** Meta object code from reading C++ file 'inputcomponent.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../src/components/inputcomponent.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inputcomponent.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_InputComponent_t {
    QByteArrayData data[8];
    char stringdata[61];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InputComponent_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InputComponent_t qt_meta_stringdata_InputComponent = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 10),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 3),
QT_MOC_LITERAL(4, 31, 11),
QT_MOC_LITERAL(5, 43, 6),
QT_MOC_LITERAL(6, 50, 8),
QT_MOC_LITERAL(7, 59, 1)
    },
    "InputComponent\0keyPressed\0\0key\0"
    "keyReleased\0update\0addCombo\0s"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InputComponent[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       4,    1,   37,    2, 0x0a /* Public */,
       5,    0,   40,    2, 0x0a /* Public */,
       6,    1,   41,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,

       0        // eod
};

void InputComponent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InputComponent *_t = static_cast<InputComponent *>(_o);
        switch (_id) {
        case 0: _t->keyPressed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->keyReleased((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->update(); break;
        case 3: _t->addCombo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject InputComponent::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_InputComponent.data,
      qt_meta_data_InputComponent,  qt_static_metacall, 0, 0}
};


const QMetaObject *InputComponent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InputComponent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InputComponent.stringdata))
        return static_cast<void*>(const_cast< InputComponent*>(this));
    return QObject::qt_metacast(_clname);
}

int InputComponent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

/****************************************************************************
** Meta object code from reading C++ file 'http.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../http.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'http.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_http_t {
    QByteArrayData data[14];
    char stringdata0[166];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_http_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_http_t qt_meta_stringdata_http = {
    {
QT_MOC_LITERAL(0, 0, 4), // "http"
QT_MOC_LITERAL(1, 5, 16), // "finish_down_load"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 15), // "transport_error"
QT_MOC_LITERAL(4, 39, 9), // "write_log"
QT_MOC_LITERAL(5, 49, 3), // "log"
QT_MOC_LITERAL(6, 53, 13), // "replyFinished"
QT_MOC_LITERAL(7, 67, 14), // "QNetworkReply*"
QT_MOC_LITERAL(8, 82, 9), // "loadError"
QT_MOC_LITERAL(9, 92, 27), // "QNetworkReply::NetworkError"
QT_MOC_LITERAL(10, 120, 11), // "readContent"
QT_MOC_LITERAL(11, 132, 12), // "loadProgress"
QT_MOC_LITERAL(12, 145, 9), // "bytesSent"
QT_MOC_LITERAL(13, 155, 10) // "bytesTotal"

    },
    "http\0finish_down_load\0\0transport_error\0"
    "write_log\0log\0replyFinished\0QNetworkReply*\0"
    "loadError\0QNetworkReply::NetworkError\0"
    "readContent\0loadProgress\0bytesSent\0"
    "bytesTotal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_http[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    1,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   54,    2, 0x08 /* Private */,
       8,    1,   57,    2, 0x08 /* Private */,
      10,    0,   60,    2, 0x08 /* Private */,
      11,    2,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   12,   13,

       0        // eod
};

void http::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<http *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->finish_down_load(); break;
        case 1: _t->transport_error(); break;
        case 2: _t->write_log((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 4: _t->loadError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 5: _t->readContent(); break;
        case 6: _t->loadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (http::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&http::finish_down_load)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (http::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&http::transport_error)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (http::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&http::write_log)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject http::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_http.data,
    qt_meta_data_http,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *http::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *http::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_http.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int http::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void http::finish_down_load()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void http::transport_error()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void http::write_log(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE

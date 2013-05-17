/****************************************************************************
** Meta object code from reading C++ file 'BabelMainWindow.hpp'
**
** Created: Sun Dec 4 23:16:31 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "BabelMainWindow.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BabelMainWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BabelMainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x0a,
      40,   16,   16,   16, 0x0a,
      62,   16,   16,   16, 0x0a,
      85,   16,   16,   16, 0x0a,
     105,   16,   16,   16, 0x0a,
     125,   16,   16,   16, 0x0a,
     149,   16,   16,   16, 0x0a,
     170,   16,   16,   16, 0x0a,
     186,   16,   16,   16, 0x0a,
     202,   16,   16,   16, 0x0a,
     229,   16,   16,   16, 0x0a,
     247,   16,   16,   16, 0x0a,
     260,   16,   16,   16, 0x0a,
     276,   16,   16,   16, 0x0a,
     313,   16,   16,   16, 0x0a,
     325,   16,   16,   16, 0x0a,
     343,  337,   16,   16, 0x0a,
     357,   16,   16,   16, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BabelMainWindow[] = {
    "BabelMainWindow\0\0setLanguageToEnglish()\0"
    "setLanguageToFrench()\0setLanguageToSpanish()\0"
    "setLanguageTo1337()\0openEmoticonFrame()\0"
    "setStatusDisconnected()\0setStatusConnected()\0"
    "setStatusBusy()\0setStatusIdle()\0"
    "customTreeViewMenu(QPoint)\0openAboutWindow()\0"
    "addContact()\0removeContact()\0"
    "doubleClickContact(QListWidgetItem*)\0"
    "startChat()\0startCall()\0index\0"
    "closeTab(int)\0disconnect()\0"
};

const QMetaObject BabelMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_BabelMainWindow,
      qt_meta_data_BabelMainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BabelMainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BabelMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BabelMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BabelMainWindow))
        return static_cast<void*>(const_cast< BabelMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int BabelMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setLanguageToEnglish(); break;
        case 1: setLanguageToFrench(); break;
        case 2: setLanguageToSpanish(); break;
        case 3: setLanguageTo1337(); break;
        case 4: openEmoticonFrame(); break;
        case 5: setStatusDisconnected(); break;
        case 6: setStatusConnected(); break;
        case 7: setStatusBusy(); break;
        case 8: setStatusIdle(); break;
        case 9: customTreeViewMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 10: openAboutWindow(); break;
        case 11: addContact(); break;
        case 12: removeContact(); break;
        case 13: doubleClickContact((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 14: startChat(); break;
        case 15: startCall(); break;
        case 16: closeTab((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: disconnect(); break;
        default: ;
        }
        _id -= 18;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

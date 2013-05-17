/****************************************************************************
** Meta object code from reading C++ file 'BabelLoginWindow.hpp'
**
** Created: Sun Dec 4 23:16:30 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "BabelLoginWindow.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BabelLoginWindow.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_BabelLoginWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x0a,
      32,   17,   17,   17, 0x0a,
      58,   17,   17,   17, 0x0a,
      83,   17,   17,   17, 0x0a,
     109,   17,   17,   17, 0x0a,
     132,   17,   17,   17, 0x0a,
     141,   17,   17,   17, 0x0a,
     159,   17,   17,   17, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_BabelLoginWindow[] = {
    "BabelLoginWindow\0\0QuitCommand()\0"
    "changeLanguageToEnglish()\0"
    "changeLanguageToFrench()\0"
    "changeLanguageToSpanish()\0"
    "changeLanguageTo1337()\0signIn()\0"
    "openAboutWindow()\0openSettings()\0"
};

const QMetaObject BabelLoginWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_BabelLoginWindow,
      qt_meta_data_BabelLoginWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &BabelLoginWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *BabelLoginWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *BabelLoginWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_BabelLoginWindow))
        return static_cast<void*>(const_cast< BabelLoginWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int BabelLoginWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: QuitCommand(); break;
        case 1: changeLanguageToEnglish(); break;
        case 2: changeLanguageToFrench(); break;
        case 3: changeLanguageToSpanish(); break;
        case 4: changeLanguageTo1337(); break;
        case 5: signIn(); break;
        case 6: openAboutWindow(); break;
        case 7: openSettings(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE

#ifndef QSINGLETONAPPLICATION_H
#define QSINGLETONAPPLICATION_H

#include <QApplication>
#include <QTranslator>
#include "BabeSingleton.hpp"
#include "BabelLoginWindow.hpp"
#include "BabelMainWindow.hpp"
#include "BabelConnectionSettings.hpp"

class QSingletonApplication : public QApplication, public Babe::Singleton<QSingletonApplication>
{
public:
    QSingletonApplication(int&, char**);

public:
  static QSingletonApplication* getSingletonPtr();
  static QSingletonApplication& getSingleton();
  void helpConsole(QWidget* parent);
  void console(QWidget* parent);
  QTranslator translator;

public:
	BabelLoginWindow* loginWindow;
	BabelMainWindow* mainWindow;
        BabelConnectionSettings* settings;
};

#endif // QSINGLETONAPPLICATION_H

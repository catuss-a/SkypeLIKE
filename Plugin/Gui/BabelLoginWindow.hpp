//
// BabelLoginWindow.hpp for  in /home/allaux_c/babel-2014-champi_d/Plugin/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sat Dec  3 01:05:47 2011 Chanh Allaux
// Last update Sun Dec  4 21:46:52 2011 alexandre champion
//

#ifndef BABELLOGINWINDOW_HPP
#define BABELLOGINWINDOW_HPP

#include <QMainWindow>
#include <QCloseEvent>
#include <QString>
#include <QKeyEvent>
#include <QTranslator>
#include <QKeyEvent>
#include <QMessageBox>
#include "BabelAboutDialog.hpp"
#include "BabelConsole.hpp"
#include "BabeCommandManager.hpp"

namespace Ui
{
  class BabelLoginWindow;
}

class BabelConnectionSettings;

class BabelLoginWindow : public QMainWindow
{
  Q_OBJECT

  friend class BabelConnectionSettings;

public:
  explicit BabelLoginWindow(QWidget *parent = 0);
  ~BabelLoginWindow();

private:
  Ui::BabelLoginWindow *ui;
  bool mSignIn;
  QString mHost;
  QString mPort;
  QString mFamily;

public:
  void signInSucceeded();
  void signInFailed(const QString&);

public slots:
  void QuitCommand();
  void changeLanguageToEnglish();
  void changeLanguageToFrench();
  void changeLanguageToSpanish();
  void changeLanguageTo1337();
  void signIn();
  void openAboutWindow();
  void openSettings();

private:
  void loadLanguage(QString const&, QString const&);

protected:
  void closeEvent(QCloseEvent *);
  void keyPressEvent(QKeyEvent *);
};

#endif // BABELLOGINWINDOW_HPP

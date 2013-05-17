//
// BabelLoginWindow.cpp for  in /home/allaux_c/babel-2014-champi_d/Plugin/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sat Dec  3 01:05:12 2011 Chanh Allaux
// Last update Sun Dec  4 21:46:48 2011 alexandre champion
//

#include "ui_babelloginwindow.h"
#include "ui_babelhelpconsole.h"
#include "BabelLoginWindow.hpp"
#include "QSingletonApplication.hpp"
#include "BabelMainWindow.hpp"
#include "BabelConnectionSettings.hpp"
#include "BabelHelpConsole.hpp"
#include "BabeCommands.hpp"

#include <map>

BabelLoginWindow::BabelLoginWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::BabelLoginWindow),
  mSignIn(false),
  mHost("127.0.0.1"),
  mPort("sip"),
  mFamily("IPv4")
{
  ui->setupUi(this);
  ui->BabelNameLineEdit->setFocus();
  connect(ui->actionAbout_Qt, SIGNAL(activated()), QSingletonApplication::getSingletonPtr(), SLOT(aboutQt()));
  this->setFixedSize(510, 371);
  loadLanguage(":/translations/babel_en", "");
  if (!Babe::NetworkManager::getSingletonPtr()->isConnected())
    openSettings();
}

BabelLoginWindow::~BabelLoginWindow()
{
  delete ui;
}

// slot
void BabelLoginWindow::QuitCommand()
{
  this->close();
  Babe::CommandManager::getSingletonPtr()->execute("quit");
}

// event
void BabelLoginWindow::closeEvent(QCloseEvent *)
{
  if (!mSignIn)
    QuitCommand();
}

void BabelLoginWindow::loadLanguage(const QString &language, const QString &comment)
{
  if (!QSingletonApplication::getSingletonPtr()->translator.load(language))
    ui->statusbar->showMessage(tr("Could not load language"), 5000);
  else
    {
      QSingletonApplication::getSingletonPtr()->installTranslator(&QSingletonApplication::getSingletonPtr()->translator);
      ui->statusbar->showMessage(comment, 5000);
    }
  ui->retranslateUi(this);
}

// slot
void BabelLoginWindow::changeLanguageToEnglish()
{
  loadLanguage(":/translations/babel_en", "Language set to english");
}

// slot
void BabelLoginWindow::changeLanguageToFrench()
{
  loadLanguage(":/translations/babel_fr", "La langue a ete changer en francais");
}

// slot
void BabelLoginWindow::changeLanguageToSpanish()
{
  loadLanguage(":/translations/babel_es", "La idioma es espanol");
}

// slot
void BabelLoginWindow::changeLanguageTo1337()
{
  loadLanguage(":/translations/babel_1337", "lAn9uA93 537 70 1337");
}

// slot
void BabelLoginWindow::openAboutWindow()
{
  BabelAboutDialog* about = new BabelAboutDialog(this);
  about->exec();
}

// slot
void BabelLoginWindow::signIn()
{
  Babe::LOG("GuiManagerImpl : [sended command \"userconnect\"]");
  Babe::CommandManager::getSingletonPtr()->execute("userconnect " +
						   ui->BabelNameLineEdit->text().toStdString() + " " +
						   ui->PasswordLineEdit->text().toStdString());
}

// slot
void BabelLoginWindow::openSettings()
{
    delete QSingletonApplication::getSingletonPtr()->settings;
    QSingletonApplication::getSingletonPtr()->settings = new BabelConnectionSettings(this);
    QSingletonApplication::getSingletonPtr()->settings->show();
}

void BabelLoginWindow::signInSucceeded()
{
  delete QSingletonApplication::getSingletonPtr()->mainWindow;
  QSingletonApplication::getSingletonPtr()->mainWindow = new BabelMainWindow(ui->BabelNameLineEdit->text());
  QMainWindow* mw = QSingletonApplication::getSingletonPtr()->mainWindow;
  mw->show();
  mw->setGeometry(this->x(), this->y(), mw->width(), mw->height());
  mSignIn = true;
  this->close();
  mSignIn = false;
}

void BabelLoginWindow::signInFailed(const QString &error)
{
  QMessageBox::critical(this, tr("Connection error"), error);
}

// evet
void BabelLoginWindow::keyPressEvent(QKeyEvent *e)
{
  if (e->key() == Qt::Key_F1 && (e->modifiers() & Qt::ShiftModifier) && (e->modifiers() & Qt::ControlModifier))
    QSingletonApplication::getSingletonPtr()->console(this);
  else if (e->key() == Qt::Key_F2 && (e->modifiers() & Qt::ShiftModifier) && (e->modifiers() & Qt::ControlModifier))
    QSingletonApplication::getSingletonPtr()->helpConsole(this);
}

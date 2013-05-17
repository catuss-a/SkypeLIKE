//
// BabelConversation.cpp for  in /home/allaux_c/babel-2014-champi_d/Plugin/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sat Dec  3 01:05:14 2011 Chanh Allaux
// Last update Sun Dec  4 20:34:34 2011 chanh allaux
//

#include <QScrollBar>
#include "BabelConversation.hpp"
#include "ui_babelconversation.h"
#include "ui_babelmainwindow.h"
#include "QSingletonApplication.hpp"
#include "BabeCommandManager.hpp"

BabelConversation::BabelConversation(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::BabelConversation)
{
  ui->setupUi(this);
  ui->retranslateUi(this);
}

BabelConversation::~BabelConversation()
{
  delete ui;
}

// slot
void BabelConversation::on_sendPushButton_clicked()
{
  QString login;
  Ui::BabelMainWindow* mwUi = QSingletonApplication::getSingletonPtr()->mainWindow->ui;
  login = mwUi->contactTabWidget->tabText(mwUi->contactTabWidget->currentIndex());
  Babe::CommandManager::getSingletonPtr()->execute("sendtext " + login.toStdString() + " " + ui->chatLineEdit->text().toStdString());
  ui->textEdit->verticalScrollBar()->setValue(ui->textEdit->verticalScrollBar()->maximum());
  ui->textEdit->insertHtml("<b>" + tr("you")  + " : </b>" + ui->chatLineEdit->text() + "<br />");
  ui->chatLineEdit->clear();
}

// slot
void BabelConversation::textLengthDisableSend(const QString & text)
{
  if (text.length() == 0)
    {
      ui->sendPushButton->setEnabled(false);
    }
  else
    {
      ui->sendPushButton->setEnabled(true);
    }
}

// slot
void BabelConversation::startCall()
{
  QSingletonApplication::getSingletonPtr()->mainWindow->requestCallFromTab();
}

// slot
void BabelConversation::suspendOrResume()
{
  QSingletonApplication::getSingletonPtr()->mainWindow->suspendOrResume(this);
}

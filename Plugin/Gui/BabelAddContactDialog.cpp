//
// BabelAddContactDialog.cpp for  in /home/allaux_c/babel-2014-champi_d/Plugin/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sat Dec  3 01:05:21 2011 Chanh Allaux
// Last update Sat Dec  3 23:33:55 2011 chanh allaux
//

#include "BabelAddContactDialog.hpp"
#include "ui_babeladdcontactdialog.h"
#include "BabelMainWindow.hpp"
#include "ui_babelmainwindow.h"
#include "QSingletonApplication.hpp"

BabelAddContactDialog::BabelAddContactDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::BabelAddContactDialog)
{
  ui->setupUi(this);
  ui->retranslateUi(this);
}

BabelAddContactDialog::~BabelAddContactDialog()
{
  delete ui;
}

// slot
void BabelAddContactDialog::addContact()
{
  if (ui->lineEdit->text().length() == 0)
    return;
  BabelMainWindow* mw = QSingletonApplication::getSingletonPtr()->mainWindow;
  if (ui->lineEdit->text() == mw->ui->loginLabel->text())
    return ;
  if (mw->ui->contactListWidget->findItems(ui->lineEdit->text(), Qt::MatchExactly).length() != 0)
    {
      mw->ui->statusbar->showMessage(tr("Contact already exists"), 5000);
    }
  else
    {
      Babe::CommandManager::getSingletonPtr()->execute("addcontact " + ui->lineEdit->text().toStdString());
      mw->addContactAction(ui->lineEdit->text(), "disconnected");
      mw->ui->statusbar->showMessage(ui->lineEdit->text() + " " + tr("has been added to your contact"), 5000);
    }
}

// slot
void BabelAddContactDialog::checkSpace(const QString& text)
{
  if (text.endsWith(' '))
    {
      QString newText = text;
      newText.remove(' ');
      ui->lineEdit->setText(newText);
    }
}

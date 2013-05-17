//
// BabelConsole.cpp for  in /home/allaux_c/babel-2014-champi_d/Plugin/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sat Dec  3 01:05:16 2011 Chanh Allaux
// Last update Sat Dec  3 01:05:16 2011 Chanh Allaux
//

#include "BabelConsole.hpp"
#include "ui_babelconsole.h"

BabelConsole::BabelConsole(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::BabelConsole)
{
  ui->setupUi(this);
  ui->retranslateUi(this);
}

BabelConsole::~BabelConsole()
{
  delete ui;
}

void BabelConsole::executeCommand()
{
  Babe::CommandManager::getSingletonPtr()->execute(ui->lineEdit->text().toStdString());
}

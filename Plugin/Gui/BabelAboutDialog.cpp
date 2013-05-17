//
// BabelAboutDialog.cpp for  in /home/allaux_c/babel-2014-champi_d/Plugin/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sat Dec  3 01:05:23 2011 Chanh Allaux
// Last update Sat Dec  3 01:05:24 2011 Chanh Allaux
//

#include "BabelAboutDialog.hpp"
#include "ui_babelaboutdialog.h"

BabelAboutDialog::BabelAboutDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::BabelAboutDialog)
{
  ui->setupUi(this);
  ui->retranslateUi(this);
}

BabelAboutDialog::~BabelAboutDialog()
{
  delete ui;
}

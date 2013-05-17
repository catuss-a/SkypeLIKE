//
// BabelConnectionSettings.cpp for  in /home/allaux_c/babel-2014-champi_d/Plugin/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sat Dec  3 01:05:17 2011 Chanh Allaux
// Last update Sat Dec  3 01:05:18 2011 Chanh Allaux
//

#include "BabelConnectionSettings.hpp"
#include "ui_babelconnectionsettings.h"
#include "QSingletonApplication.hpp"
#include "BabelLoginWindow.hpp"
#include "BabeApplicationSettings.hpp"

BabelConnectionSettings::BabelConnectionSettings(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::BabelConnectionSettings)
{
  ui->setupUi(this);
  ui->retranslateUi(this);
  Babe::ApplicationSettings* settings = Babe::ApplicationSettings::getSingletonPtr();
  ui->hostLineEdit->setText(settings->getSystemAttribute("NetworkSystem", "host").c_str());
}

BabelConnectionSettings::~BabelConnectionSettings()
{
  delete ui;
}

void BabelConnectionSettings::validateSettings()
{
  BabelLoginWindow* loginWindow = QSingletonApplication::getSingletonPtr()->loginWindow;
  loginWindow->mHost = ui->hostLineEdit->text();
  loginWindow->mPort = ui->portLineEdit->text();
  loginWindow->mFamily = ui->familyComboBox->itemText(ui->familyComboBox->currentIndex());
  Babe::CommandManager::getSingletonPtr()->execute("connect " + loginWindow->mHost.toStdString() + " " +  loginWindow->mPort.toStdString() +
						   " " + loginWindow->mFamily.toStdString());
  this->close();
}

//
// BabelAddContactDialog.hpp for  in /home/allaux_c/babel-2014-champi_d/Plugin/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sat Dec  3 01:06:31 2011 Chanh Allaux
// Last update Sat Dec  3 01:06:32 2011 Chanh Allaux
//

#ifndef BABELADDCONTACTDIALOG_HPP
#define BABELADDCONTACTDIALOG_HPP

#include <QDialog>
#include "BabelMainWindow.hpp"

namespace Ui
{
  class BabelAddContactDialog;
}

class BabelAddContactDialog : public QDialog
{
  Q_OBJECT

  public:
  explicit BabelAddContactDialog(QWidget *parent = 0);
  ~BabelAddContactDialog();

public slots:
  void addContact();
  void checkSpace(const QString&);

private:
  Ui::BabelAddContactDialog *ui;
};

#endif // BABELADDCONTACTDIALOG_HPP

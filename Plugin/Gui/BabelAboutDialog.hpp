//
// BabelAboutDialog.hpp for  in /home/allaux_c/babel-2014-champi_d/Plugin/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sat Dec  3 01:06:30 2011 Chanh Allaux
// Last update Sat Dec  3 01:06:30 2011 Chanh Allaux
//

#ifndef BabelAboutDialog_HPP
#define BabelAboutDialog_HPP

#include <QDialog>

namespace Ui
{
  class BabelAboutDialog;
}

class BabelAboutDialog : public QDialog
{
  Q_OBJECT

  public:
  explicit BabelAboutDialog(QWidget *parent = 0);
  ~BabelAboutDialog();

private:
  Ui::BabelAboutDialog *ui;
};

#endif // BabelAboutDialog_HPP

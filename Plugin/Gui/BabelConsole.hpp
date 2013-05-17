//
// BabelConsole.hpp for  in /home/allaux_c/babel-2014-champi_d/Plugin/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sat Dec  3 01:06:07 2011 Chanh Allaux
// Last update Sat Dec  3 01:06:08 2011 Chanh Allaux
//

#ifndef BABELCONSOLE_HPP
#define BABELCONSOLE_HPP

#include <QDialog>
#include "Babe.hpp"

namespace Ui
{
  class BabelConsole;
}

class BabelConsole : public QDialog
{
  Q_OBJECT

  public:
  explicit BabelConsole(QWidget *parent = 0);
  ~BabelConsole();

public slots:
  void executeCommand();

private:
  Ui::BabelConsole *ui;
};

#endif // BABELCONSOLE_HPP

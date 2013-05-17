//
// BabelConnectionSettings.hpp for  in /home/allaux_c/babel-2014-champi_d/Plugin/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sat Dec  3 01:06:10 2011 Chanh Allaux
// Last update Sat Dec  3 01:06:14 2011 Chanh Allaux
//

#ifndef BABELCONNECTIONSETTINGS_HPP
#define BABELCONNECTIONSETTINGS_HPP

#include <QDialog>

namespace Ui
{
  class BabelConnectionSettings;
}

class BabelConnectionSettings : public QDialog
{
  Q_OBJECT

  public:
  explicit BabelConnectionSettings(QWidget *parent = 0);
  ~BabelConnectionSettings();

public slots:
  void validateSettings();

private:
  Ui::BabelConnectionSettings *ui;
};

#endif // BABELCONNECTIONSETTINGS_HPP

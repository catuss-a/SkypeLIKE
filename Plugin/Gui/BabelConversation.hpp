//
// BabelConversation.hpp for  in /home/allaux_c/babel-2014-champi_d/Plugin/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sat Dec  3 01:05:56 2011 Chanh Allaux
// Last update Sat Dec  3 01:06:00 2011 Chanh Allaux
//

#ifndef BABELCONVERSATION_HPP
#define BABELCONVERSATION_HPP

#include <QWidget>

namespace Ui
{
  class BabelConversation;
}

class BabelMainWindow;

class BabelConversation : public QWidget
{
  Q_OBJECT

  friend class BabelMainWindow;

public:
  explicit BabelConversation(QWidget *parent = 0);
  ~BabelConversation();

public slots:
  void on_sendPushButton_clicked();
  void textLengthDisableSend(const QString &);
  void startCall();
  void suspendOrResume();

private:
  Ui::BabelConversation *ui;
};

#endif // BABELCONVERSATION_HPP

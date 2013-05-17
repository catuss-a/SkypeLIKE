//
// BabelNotifications.hpp for  in /home/allaux_c/babel-2014-champi_d/Plugin/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sat Dec  3 01:05:31 2011 Chanh Allaux
// Last update Sun Dec  4 19:42:02 2011 alexandre champion
//

#ifndef BABELNOTIFICATIONS_HPP
#define BABELNOTIFICATIONS_HPP

#include <QTranslator>
#include <string>
#include <QMap>
#include "Babe.hpp"
#include "BabeCommandParser.hpp"
#include "QSingletonApplication.hpp"

class BabelNotifications
{
public:
  BabelNotifications();
  void notify(const std::string&);

private:
  void userConnectionSucceeded(Babe::CommandParser::ArgVector&);
  void userConnectionFailed(Babe::CommandParser::ArgVector&);
  void userStatus(Babe::CommandParser::ArgVector&);
  void contactRequest(Babe::CommandParser::ArgVector&);
  void callRequest(Babe::CommandParser::ArgVector&);
  void error(Babe::CommandParser::ArgVector&);
  void callAccepted(Babe::CommandParser::ArgVector&);
  void callRejected(Babe::CommandParser::ArgVector&);
  void callHungUp(Babe::CommandParser::ArgVector&);
  void callResumed(Babe::CommandParser::ArgVector&);
  void callSuspended(Babe::CommandParser::ArgVector&);
  void unknownContact(Babe::CommandParser::ArgVector&);
  void connectionLost(Babe::CommandParser::ArgVector&);
  void receiveText(Babe::CommandParser::ArgVector&);
  bool check();

private:
  typedef void (BabelNotifications::*notificationFunction)(Babe::CommandParser::ArgVector&);
  typedef QMap<std::string, notificationFunction> NotificationMap;
  NotificationMap mNotificationMap;
  Babe::CommandParser* mCommandParser;
};

#endif // BABELNOTIFICATIONS_HPP

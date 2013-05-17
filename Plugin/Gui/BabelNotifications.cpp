//
// BabelNotifications.cpp for  in /home/allaux_c/babel-2014-champi_d/Plugin/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sat Dec  3 01:02:07 2011 Chanh Allaux
// Last update Sun Dec  4 23:00:50 2011 alexandre champion
//

#include "BabelNotifications.hpp"

BabelNotifications::BabelNotifications()
  : mCommandParser(new Babe::CommandParser)
{
  mNotificationMap["userconnectionsucceeded"] = &BabelNotifications::userConnectionSucceeded;
  mNotificationMap["userconnectionfailed"] = &BabelNotifications::userConnectionFailed;
  mNotificationMap["userstatus"] = &BabelNotifications::userStatus;
  mNotificationMap["callrequest"] = &BabelNotifications::callRequest;
  mNotificationMap["contactrequest"] = &BabelNotifications::contactRequest;
  mNotificationMap["error"] = &BabelNotifications::error;
  mNotificationMap["callaccepted"] = &BabelNotifications::callAccepted;
  mNotificationMap["callrejected"] = &BabelNotifications::callRejected;
  mNotificationMap["callhungup"] = &BabelNotifications::callHungUp;
  mNotificationMap["callresumed"] = &BabelNotifications::callResumed;
  mNotificationMap["callsuspended"] = &BabelNotifications::callSuspended;
  mNotificationMap["connectionlost"] = &BabelNotifications::connectionLost;
  mNotificationMap["unknowncontact"] = &BabelNotifications::unknownContact;
  mNotificationMap["receivetext"] = &BabelNotifications::receiveText;
}

//----------------------------------Notifications---------------------------------------------//

bool BabelNotifications::check()
{
  if (QSingletonApplication::getSingletonPtr()->mainWindow == NULL)
    return false;
  return true;
}

void BabelNotifications::userConnectionSucceeded(Babe::CommandParser::ArgVector&)
{
  Babe::LOG("GUI NOTIFICATION: userConnectionSucceeded");
  QSingletonApplication::getSingletonPtr()->loginWindow->signInSucceeded();
}

void BabelNotifications::userConnectionFailed(Babe::CommandParser::ArgVector& args)
{
  Babe::LOG("GUI NOTIFICATION: userConnectionFailed");
  if (args.size() < 1)
    {
      Babe::LOG("GUI NOTIFICATION: userConnectionFailed: bad arg count");
      return ;
    }
  QString error("");
  for (Babe::CommandParser::ArgVector::iterator i = args.begin(); i != args.end(); ++i)
    {
      error += (*i).c_str();
      error += " ";
    }
  QSingletonApplication::getSingletonPtr()->loginWindow->signInFailed(error);
}

void BabelNotifications::userStatus(Babe::CommandParser::ArgVector& args)
{
  if (!check())
    return ;
  Babe::LOG("GUI NOTIFICATION: userStatus");
  if (args.size() < 2)
    {
      Babe::LOGE("GUI NOTIFICATION: userStatus: bad arg count");
      return ;
    }
  QString login = args.front().c_str();
  args.pop_front();
  QString status = args.front().c_str();
  QSingletonApplication::getSingletonPtr()->mainWindow->addContactAction(login, status);
}

void BabelNotifications::contactRequest(Babe::CommandParser::ArgVector& args)
{
  if (!check())
    return ;
  if (args.size() < 1)
    {
      Babe::LOGE("GUI NOTIFICATION: contactRequest: bad arg count");
      return ;
    }
  QString login = args.front().c_str();
  QSingletonApplication::getSingletonPtr()->mainWindow->contactRequest(login);
}

void BabelNotifications::callRequest(Babe::CommandParser::ArgVector& args)
{
  if (!check())
    return ;
  if (args.size() < 1)
    {
      Babe::LOGE("GUI NOTIFICATION: callRequest: bad arg count");
      return ;
    }
  QString login = args.front().c_str();
  QSingletonApplication::getSingletonPtr()->mainWindow->callRequest(login);
}

void BabelNotifications::error(Babe::CommandParser::ArgVector& args)
{
  if (args.size() < 1)
    {
      Babe::LOGE("GUI NOTIFICATION: error: bad arg count");
    }
  QString error("");
  for (Babe::CommandParser::ArgVector::iterator i = args.begin(); i != args.end(); ++i)
    {
      error += (*i).c_str();
      error += " ";
    }
  QMessageBox::critical(QSingletonApplication::getSingletonPtr()->loginWindow, "Error", error);
}

void BabelNotifications::callAccepted(Babe::CommandParser::ArgVector& args)
{
  if (!check())
    return ;
  if (args.size() < 1)
    {
      Babe::LOGE("GUI NOTIFICATION: callAccepted: bad arg count");
      return ;
    }
  QString login = args.front().c_str();
  QSingletonApplication::getSingletonPtr()->mainWindow->callAccepted(login);
}

void BabelNotifications::callRejected(Babe::CommandParser::ArgVector& args)
{
  if (!check())
    return ;
  if (args.size() < 1)
    {
      Babe::LOGE("GUI NOTIFICATION: callRejected: bad arg count");
      return ;
    }
  QString login = args.front().c_str();
  QSingletonApplication::getSingletonPtr()->mainWindow->callRejected(login);
}

void BabelNotifications::callHungUp(Babe::CommandParser::ArgVector& args)
{
  if (!check())
    return ;
  if (args.size() < 1)
    {
      Babe::LOGE("GUI NOTIFICATION: callHungUp: bad arg count");
      return ;
    }
  QString login = args.front().c_str();
  QSingletonApplication::getSingletonPtr()->mainWindow->callHungUp(login);
}

void BabelNotifications::callResumed(Babe::CommandParser::ArgVector& args)
{
  if (!check())
    return ;
  if (args.size() < 1)
    {
      Babe::LOGE("GUI NOTIFICATION: callResumed: bad arg count");
      return ;
    }
  QString login = args.front().c_str();
  QSingletonApplication::getSingletonPtr()->mainWindow->callResumed(login);
}

void BabelNotifications::callSuspended(Babe::CommandParser::ArgVector& args)
{
  if (!check())
    return ;
  if (args.size() < 1)
    {
      Babe::LOGE("GUI NOTIFICATION: callSuspended: bad arg count");
      return ;
    }
  QString login = args.front().c_str();
  QSingletonApplication::getSingletonPtr()->mainWindow->callSuspended(login);
}

void BabelNotifications::unknownContact(Babe::CommandParser::ArgVector& args)
{
  std::cout << "pute" << std::endl;
  if (!check())
    return ;
  if (args.size() < 1)
    {
      Babe::LOGE("GUI NOTIFICATION: unknownContact: bad arg count");
      return ;
    }
  QString message("");
  for (Babe::CommandParser::ArgVector::iterator i = args.begin(); i != args.end(); ++i)
    {
      message += (*i).c_str();
      message += " ";
    }
  QSingletonApplication::getSingletonPtr()->mainWindow->unknownContact(message);
}

void BabelNotifications::connectionLost(Babe::CommandParser::ArgVector&)
{
    if (!check())
      return ;
    QSingletonApplication::getSingletonPtr()->mainWindow->connectionLost();
}

void BabelNotifications::receiveText(Babe::CommandParser::ArgVector& args)
{
  if (!check())
    return ;
  if (args.size() < 2)
    {
      Babe::LOGE("GUI NOTIFICATION: receiveText: bad arg count");
      return ;
    }
  QString login = args.front().c_str();
  args.pop_front();
  QString message("");
  for (Babe::CommandParser::ArgVector::iterator i = args.begin(); i != args.end(); ++i)
    {
      message += (*i).c_str();
      message += " ";
    }
  QSingletonApplication::getSingletonPtr()->mainWindow->receiveText(login, message);
}

//--------------------------------------------------------------------------------------------//

void BabelNotifications::notify(const std::string& notification)
{
  Babe::CommandParser::ParsedCommand pc = mCommandParser->parseCommand(notification);
  if (mNotificationMap.find(pc.name) != mNotificationMap.end())
    (this->*mNotificationMap[pc.name])(pc.args);
}

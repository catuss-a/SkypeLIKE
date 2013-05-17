//
// UserConnectionFailedCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
//
// Made by alexandre champion
// Login   <champi_d@epitech.net>
//
// Started on  Thu Dec  1 14:01:36 2011 alexandre champion
// Last update Fri Dec  2 21:14:21 2011 alexandre champion
//

#include "UserConnectionFailedCmd.hpp"

UserConnectionFailedCmd::UserConnectionFailedCmd(std::string const& errorMessage)
  : Babe::ICommand(LOW),
    mName("userconnectionfailed"),
    mErrorMessage(errorMessage),
    mStringified(mName + " " + mErrorMessage)
{
}

UserConnectionFailedCmd::UserConnectionFailedCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("userconnectionfailed")
{
  if (args.size() < 1)
    return ;
  for (Babe::CommandParser::ArgVector::iterator i = args.begin(); i != args.end(); ++i)
    mErrorMessage += (*i) + " ";
  mStringified = mName + " " + mErrorMessage;
}

UserConnectionFailedCmd::~UserConnectionFailedCmd()
{
}

void UserConnectionFailedCmd::exec()
{
  Babe::GuiManager::getSingletonPtr()->notify(mStringified);
  Babe::CommandManager::getSingletonPtr()->setReturnMessage("GuiManager notified \"" + mStringified + "\"");
}

std::string const& UserConnectionFailedCmd::getName() const
{
  return mName;
}

std::string const& UserConnectionFailedCmd::stringify()
{
  return mStringified;
}

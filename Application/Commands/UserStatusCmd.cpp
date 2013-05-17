//
// UserStatusCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 22:02:56 2011 alexandre champion
// Last update Thu Dec  1 22:21:54 2011 alexandre champion
//

#include "UserStatusCmd.hpp"

UserStatusCmd::UserStatusCmd(std::string const& login, std::string const& status)
  : Babe::ICommand(LOW),
    mName("userstatus"),
    mLogin(login),
    mStatus(status)
{
  mStringified = mName + " " + mLogin + " " + mStatus;
}

UserStatusCmd::UserStatusCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("userstatus")
{
  if (args.size() < 2)
    return ;
  mLogin = args.front();
  args.pop_front();
  mStatus = args.front();
  mStringified = mName + " " + mLogin + " " + mStatus;
}

UserStatusCmd::~UserStatusCmd()
{
}

void UserStatusCmd::exec()
{
  Babe::GuiManager::getSingletonPtr()->notify(mStringified);
  Babe::CommandManager::getSingletonPtr()->setReturnMessage("GuiManager notified \"" + mStringified + "\"");
}

std::string const& UserStatusCmd::getName() const
{
  return mName;
}

std::string const& UserStatusCmd::stringify()
{
  return mStringified;
}

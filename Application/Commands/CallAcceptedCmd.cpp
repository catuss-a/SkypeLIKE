//
// CallAcceptedCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 23:49:57 2011 alexandre champion
// Last update Fri Dec  2 17:33:26 2011 alexandre champion
//

#include "CallAcceptedCmd.hpp"

CallAcceptedCmd::CallAcceptedCmd(std::string const& login)
  : Babe::ICommand(LOW),
    mName("callaccepted"),
    mLogin(login)
{
  mStringified = mName + " " + mLogin;
}

CallAcceptedCmd::CallAcceptedCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("callaccepted")
{
  if (args.size() < 1)
    return ;
  mLogin = args.front();
  mStringified = mName + " " + mLogin;
}

CallAcceptedCmd::~CallAcceptedCmd()
{
}

void CallAcceptedCmd::exec()
{
  Babe::GuiManager::getSingletonPtr()->notify(mStringified);
  Babe::CommandManager::getSingletonPtr()->setReturnMessage("GuiManager notified \"" + mStringified + "\"");
  Babe::AudioManager::getSingletonPtr()->on();
}

std::string const& CallAcceptedCmd::getName() const
{
  return mName;
}

std::string const& CallAcceptedCmd::stringify()
{
  return mStringified;
}

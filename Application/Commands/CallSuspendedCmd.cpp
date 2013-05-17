//
// CallSuspendedCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Fri Dec  2 16:48:19 2011 alexandre champion
// Last update Fri Dec  2 17:38:43 2011 alexandre champion
//

#include "CallSuspendedCmd.hpp"

CallSuspendedCmd::CallSuspendedCmd(std::string const& login)
  : Babe::ICommand(LOW),
    mName("callsuspended"),
    mLogin(login)
{
  mStringified = mName + " " + mLogin;
}

CallSuspendedCmd::CallSuspendedCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("callsuspended")
{
  if (args.size() < 1)
    return ;
  mLogin = args.front();
  mStringified = mName + " " + mLogin;
}

CallSuspendedCmd::~CallSuspendedCmd()
{
}

void CallSuspendedCmd::exec()
{
  Babe::GuiManager::getSingletonPtr()->notify(mStringified);
  Babe::CommandManager::getSingletonPtr()->setReturnMessage("GuiManager notified \"" + mStringified + "\"");
  Babe::AudioManager::getSingletonPtr()->off();
}

std::string const& CallSuspendedCmd::getName() const
{
  return mName;
}

std::string const& CallSuspendedCmd::stringify()
{
  return mStringified;
}

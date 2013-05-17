//
// CallRejectedCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 23:56:59 2011 alexandre champion
// Last update Thu Dec  1 23:57:39 2011 alexandre champion
//

#include "CallRejectedCmd.hpp"

CallRejectedCmd::CallRejectedCmd(std::string const& login)
  : Babe::ICommand(LOW),
    mName("callrejected"),
    mLogin(login)
{
  mStringified = mName + " " + mLogin;
}

CallRejectedCmd::CallRejectedCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("callrejected")
{
  if (args.size() < 1)
    return ;
  mLogin = args.front();
  mStringified = mName + " " + mLogin;
}

CallRejectedCmd::~CallRejectedCmd()
{
}

void CallRejectedCmd::exec()
{
  Babe::GuiManager::getSingletonPtr()->notify(mStringified);
  Babe::CommandManager::getSingletonPtr()->setReturnMessage("GuiManager notified \"" + mStringified + "\"");
}

std::string const& CallRejectedCmd::getName() const
{
  return mName;
}

std::string const& CallRejectedCmd::stringify()
{
  return mStringified;
}

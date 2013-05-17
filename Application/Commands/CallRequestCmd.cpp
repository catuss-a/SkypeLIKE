//
// CallRequestCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 23:41:37 2011 alexandre champion
// Last update Sun Dec  4 23:00:14 2011 alexandre champion
//

#include "CallRequestCmd.hpp"

CallRequestCmd::CallRequestCmd(std::string const& login)
  : Babe::ICommand(LOW),
    mName("callrequest"),
    mLogin(login)
{
  mStringified = mName + " " + mLogin;
}

CallRequestCmd::CallRequestCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("callrequest")
{
  if (args.size() < 1)
    return ;
  mLogin = args.front();
  mStringified = mName + " " + mLogin;
}

CallRequestCmd::~CallRequestCmd()
{
}

void CallRequestCmd::exec()
{
  Babe::GuiManager::getSingletonPtr()->notify(mStringified);
  Babe::CommandManager::getSingletonPtr()->setReturnMessage("GuiManager notified \"" + mStringified + "\"");
}

std::string const& CallRequestCmd::getName() const
{
  return mName;
}

std::string const& CallRequestCmd::stringify()
{
  return mStringified;
}

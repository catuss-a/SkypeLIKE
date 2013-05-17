//
// ContactRequestCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 22:31:09 2011 alexandre champion
// Last update Thu Dec  1 22:33:45 2011 alexandre champion
//

#include "ContactRequestCmd.hpp"

ContactRequestCmd::ContactRequestCmd(std::string const& login)
  : Babe::ICommand(LOW),
    mName("contactrequest"),
    mLogin(login)
{
  mStringified = mName + " " + mLogin;
}

ContactRequestCmd::ContactRequestCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("contactrequest")
{
  if (args.size() < 1)
    return ;
  mLogin = args.front();
  mStringified = mName + " " + mLogin;
}

ContactRequestCmd::~ContactRequestCmd()
{
}

void ContactRequestCmd::exec()
{
  Babe::GuiManager::getSingletonPtr()->notify(mStringified);
  Babe::CommandManager::getSingletonPtr()->setReturnMessage("GuiManager notified \"" + mStringified + "\"");
}

std::string const& ContactRequestCmd::getName() const
{
  return mName;
}

std::string const& ContactRequestCmd::stringify()
{
  return mStringified;
}

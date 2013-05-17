//
// CallHungUpCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Fri Dec  2 16:37:04 2011 alexandre champion
// Last update Fri Dec  2 17:37:50 2011 alexandre champion
//

#include "CallHungUpCmd.hpp"

CallHungUpCmd::CallHungUpCmd(std::string const& login)
  : Babe::ICommand(LOW),
    mName("callhungup"),
    mLogin(login)
{
  mStringified = mName + " " + mLogin;
}

CallHungUpCmd::CallHungUpCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("callhungup")
{
  if (args.size() < 1)
    return ;
  mLogin = args.front();
  mStringified = mName + " " + mLogin;
}

CallHungUpCmd::~CallHungUpCmd()
{
}

void CallHungUpCmd::exec()
{
  Babe::GuiManager::getSingletonPtr()->notify(mStringified);
  Babe::CommandManager::getSingletonPtr()->setReturnMessage("GuiManager notified \"" + mStringified + "\"");
  Babe::AudioManager::getSingletonPtr()->off();
}

std::string const& CallHungUpCmd::getName() const
{
  return mName;
}

std::string const& CallHungUpCmd::stringify()
{
  return mStringified;
}

//
// CallResumedCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Fri Dec  2 16:57:11 2011 alexandre champion
// Last update Fri Dec  2 17:39:19 2011 alexandre champion
//

#include "CallResumedCmd.hpp"

CallResumedCmd::CallResumedCmd(std::string const& login)
  : Babe::ICommand(LOW),
    mName("callresumed"),
    mLogin(login)
{
  mStringified = mName + " " + mLogin;
}

CallResumedCmd::CallResumedCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("callresumed")
{
  if (args.size() < 1)
    return ;
  mLogin = args.front();
  mStringified = mName + " " + mLogin;
}

CallResumedCmd::~CallResumedCmd()
{
}

void CallResumedCmd::exec()
{
  Babe::GuiManager::getSingletonPtr()->notify(mStringified);
  Babe::CommandManager::getSingletonPtr()->setReturnMessage("GuiManager notified \"" + mStringified + "\"");
  Babe::AudioManager::getSingletonPtr()->on();
}

std::string const& CallResumedCmd::getName() const
{
  return mName;
}

std::string const& CallResumedCmd::stringify()
{
  return mStringified;
}

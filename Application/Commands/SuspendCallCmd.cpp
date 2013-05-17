//
// SuspendCallCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Fri Dec  2 16:42:03 2011 alexandre champion
// Last update Fri Dec  2 17:38:35 2011 alexandre champion
//

#include "SuspendCallCmd.hpp"

SuspendCallCmd::SuspendCallCmd(std::string const& login)
  : Babe::ICommand(LOW),
    mName("suspendcall"),
    mLogin(login)
{
  mStringified = mName + " " + mLogin;
}

SuspendCallCmd::SuspendCallCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("suspendcall")
{
  if (args.size() < 1)
    return ;
  mLogin = args.front();
  mStringified = mName + " " + mLogin;
}

SuspendCallCmd::~SuspendCallCmd()
{
}

void SuspendCallCmd::exec()
{
  if (Babe::NetworkManager::getSingletonPtr()->sendMessage(mStringified))
    {
      Babe::CommandManager::getSingletonPtr()->setReturnMessage("NetworkManager sended the message \"" + mStringified + "\"");
      Babe::AudioManager::getSingletonPtr()->off();
    }
  else
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("Failed to send the message \"" + mStringified + "\"");
}

std::string const& SuspendCallCmd::getName() const
{
  return mName;
}

std::string const& SuspendCallCmd::stringify()
{
  return mStringified;
}

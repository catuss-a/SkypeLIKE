//
// HangUpCallCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Fri Dec  2 00:00:05 2011 alexandre champion
// Last update Fri Dec  2 17:37:04 2011 alexandre champion
//

#include "HangUpCallCmd.hpp"

HangUpCallCmd::HangUpCallCmd(std::string const& login)
  : Babe::ICommand(LOW),
    mName("hangupcall"),
    mLogin(login)
{
  mStringified = mName + " " + mLogin;
}

HangUpCallCmd::HangUpCallCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("hangupcall")
{
  if (args.size() < 1)
    return ;
  mLogin = args.front();
  mStringified = mName + " " + mLogin;
}

HangUpCallCmd::~HangUpCallCmd()
{
}

void HangUpCallCmd::exec()
{
  if (Babe::NetworkManager::getSingletonPtr()->sendMessage(mStringified))
    {
      Babe::CommandManager::getSingletonPtr()->setReturnMessage("NetworkManager sended the message \"" + mStringified + "\"");
      Babe::AudioManager::getSingletonPtr()->off();
    }
  else
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("Failed to send the message \"" + mStringified + "\"");
}

std::string const& HangUpCallCmd::getName() const
{
  return mName;
}

std::string const& HangUpCallCmd::stringify()
{
  return mStringified;
}

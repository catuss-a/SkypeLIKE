//
// AcceptCallCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 23:46:18 2011 alexandre champion
// Last update Fri Dec  2 17:33:02 2011 alexandre champion
//

#include "AcceptCallCmd.hpp"

AcceptCallCmd::AcceptCallCmd(std::string const& login)
  : Babe::ICommand(LOW),
    mName("acceptcall"),
    mLogin(login)
{
  mStringified = mName + " " + mLogin;
}

AcceptCallCmd::AcceptCallCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("acceptcall")
{
  if (args.size() < 1)
    return ;
  mLogin = args.front();
  mStringified = mName + " " + mLogin;
}

AcceptCallCmd::~AcceptCallCmd()
{
}

void AcceptCallCmd::exec()
{
  if (Babe::NetworkManager::getSingletonPtr()->sendMessage(mStringified))
    {
      Babe::CommandManager::getSingletonPtr()->setReturnMessage("NetworkManager sended the message \"" + mStringified + "\"");
      Babe::AudioManager::getSingletonPtr()->on();
    }
  else
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("Failed to send the message \"" + mStringified + "\"");
}

std::string const& AcceptCallCmd::getName() const
{
  return mName;
}

std::string const& AcceptCallCmd::stringify()
{
  return mStringified;
}

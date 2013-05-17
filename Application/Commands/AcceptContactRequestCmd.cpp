//
// AcceptContactRequestCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 22:37:05 2011 alexandre champion
// Last update Thu Dec  1 22:38:03 2011 alexandre champion
//

#include "AcceptContactRequestCmd.hpp"

AcceptContactRequestCmd::AcceptContactRequestCmd(std::string const& login)
  : Babe::ICommand(LOW),
    mName("acceptcontactrequest"),
    mLogin(login)
{
  mStringified = mName + " " + mLogin;
}

AcceptContactRequestCmd::AcceptContactRequestCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("acceptcontactrequest")
{
  if (args.size() < 1)
    return ;
  mLogin = args.front();
  mStringified = mName + " " + mLogin;
}

AcceptContactRequestCmd::~AcceptContactRequestCmd()
{
}

void AcceptContactRequestCmd::exec()
{
  if (Babe::NetworkManager::getSingletonPtr()->sendMessage(mStringified))
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("NetworkManager sended the message \"" + mStringified + "\"");
  else
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("Failed to send the message \"" + mStringified + "\"");
}

std::string const& AcceptContactRequestCmd::getName() const
{
  return mName;
}

std::string const& AcceptContactRequestCmd::stringify()
{
  return mStringified;
}

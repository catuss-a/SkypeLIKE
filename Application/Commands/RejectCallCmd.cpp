//
// RejectCallCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 23:53:44 2011 alexandre champion
// Last update Thu Dec  1 23:54:42 2011 alexandre champion
//

#include "RejectCallCmd.hpp"

RejectCallCmd::RejectCallCmd(std::string const& login)
  : Babe::ICommand(LOW),
    mName("rejectcall"),
    mLogin(login)
{
  mStringified = mName + " " + mLogin;
}

RejectCallCmd::RejectCallCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("rejectcall")
{
  if (args.size() < 1)
    return ;
  mLogin = args.front();
  mStringified = mName + " " + mLogin;
}

RejectCallCmd::~RejectCallCmd()
{
}

void RejectCallCmd::exec()
{
  if (Babe::NetworkManager::getSingletonPtr()->sendMessage(mStringified))
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("NetworkManager sended the message \"" + mStringified + "\"");
  else
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("Failed to send the message \"" + mStringified + "\"");
}

std::string const& RejectCallCmd::getName() const
{
  return mName;
}

std::string const& RejectCallCmd::stringify()
{
  return mStringified;
}

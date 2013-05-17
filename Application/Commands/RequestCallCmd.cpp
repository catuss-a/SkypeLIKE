//
// RequestCallCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 23:37:01 2011 alexandre champion
// Last update Thu Dec  1 23:38:07 2011 alexandre champion
//

#include "RequestCallCmd.hpp"

RequestCallCmd::RequestCallCmd(std::string const& login)
  : Babe::ICommand(LOW),
    mName("requestcall"),
    mLogin(login)
{
  mStringified = mName + " " + mLogin;
}

RequestCallCmd::RequestCallCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("requestcall")
{
  if (args.size() < 1)
    return ;
  mLogin = args.front();
  mStringified = mName + " " + mLogin;
}

RequestCallCmd::~RequestCallCmd()
{
}

void RequestCallCmd::exec()
{
  if (Babe::NetworkManager::getSingletonPtr()->sendMessage(mStringified))
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("NetworkManager sended the message \"" + mStringified + "\"");
  else
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("Failed to send the message \"" + mStringified + "\"");
}

std::string const& RequestCallCmd::getName() const
{
  return mName;
}

std::string const& RequestCallCmd::stringify()
{
  return mStringified;
}

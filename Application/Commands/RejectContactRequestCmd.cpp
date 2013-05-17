//
// RejectContactRequestCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 23:18:49 2011 alexandre champion
// Last update Thu Dec  1 23:20:18 2011 alexandre champion
//

#include "RejectContactRequestCmd.hpp"

RejectContactRequestCmd::RejectContactRequestCmd(std::string const& login)
  : Babe::ICommand(LOW),
    mName("rejectcontactrequest"),
    mLogin(login)
{
  mStringified = mName + " " + mLogin;
}

RejectContactRequestCmd::RejectContactRequestCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("rejectcontactrequest")
{
  if (args.size() < 1)
    return ;
  mLogin = args.front();
  mStringified = mName + " " + mLogin;
}

RejectContactRequestCmd::~RejectContactRequestCmd()
{
}

void RejectContactRequestCmd::exec()
{
  if (Babe::NetworkManager::getSingletonPtr()->sendMessage(mStringified))
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("NetworkManager sended the message \"" + mStringified + "\"");
  else
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("Failed to send the message \"" + mStringified + "\"");
}

std::string const& RejectContactRequestCmd::getName() const
{
  return mName;
}

std::string const& RejectContactRequestCmd::stringify()
{
  return mStringified;
}

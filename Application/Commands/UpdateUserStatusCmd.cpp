//
// UpdateUserStatusCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 22:11:48 2011 alexandre champion
// Last update Thu Dec  1 22:15:39 2011 alexandre champion
//

#include "UpdateUserStatusCmd.hpp"

UpdateUserStatusCmd::UpdateUserStatusCmd(std::string const& status)
  : Babe::ICommand(LOW),
    mName("updateuserstatus"),
    mStatus(status)
{
  mStringified = mName + " " + mStatus;
}

UpdateUserStatusCmd::UpdateUserStatusCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("updateuserstatus")
{
  if (args.size() < 1)
    return ;
  mStatus = args.front();
  mStringified = mName + " " + mStatus;
}

UpdateUserStatusCmd::~UpdateUserStatusCmd()
{
}

void UpdateUserStatusCmd::exec()
{
  if (Babe::NetworkManager::getSingletonPtr()->sendMessage(mStringified))
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("NetworkManager sended the message \"" + mStringified + "\"");
  else
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("Failed to send the message \"" + mStringified + "\"");
}

std::string const& UpdateUserStatusCmd::getName() const
{
  return mName;
}

std::string const& UpdateUserStatusCmd::stringify()
{
  return mStringified;
}

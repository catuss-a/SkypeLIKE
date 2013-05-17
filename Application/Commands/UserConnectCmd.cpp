//
// UserConnectCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Wed Nov 30 18:02:00 2011 alexandre champion
// Last update Thu Dec  1 14:48:16 2011 alexandre champion
//

#include "UserConnectCmd.hpp"

UserConnectCmd::UserConnectCmd(std::string const& userName, std::string const& userPassword)
  : Babe::ICommand(LOW),
    mName("userconnect"),
    mUserName(userName),
    mUserPassword(userPassword)
{
  mStringified = mName + " " + mUserName + " " + mUserPassword;
}

UserConnectCmd::UserConnectCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
	mName("userconnect")
{
  if (args.size() < 2)
    return ;
  mUserName = args.front();
  args.pop_front();
  mUserPassword = args.front();
  mStringified = mName + " " + mUserName + " " + mUserPassword;
}

UserConnectCmd::~UserConnectCmd()
{
}

void UserConnectCmd::exec()
{
  if (Babe::NetworkManager::getSingletonPtr()->sendMessage(mStringified))
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("NetworkManager sended the message \"" + mStringified + "\"");
  else
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("Failed to send the message \"" + mStringified + "\"");
}

std::string const& UserConnectCmd::getName() const
{
  return mName;
}

std::string const& UserConnectCmd::stringify()
{
  return mStringified;
}

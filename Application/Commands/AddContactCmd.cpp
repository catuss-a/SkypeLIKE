//
// AddContactCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 22:27:04 2011 alexandre champion
// Last update Thu Dec  1 22:28:40 2011 alexandre champion
//

#include "AddContactCmd.hpp"

AddContactCmd::AddContactCmd(std::string const& login)
  : Babe::ICommand(LOW),
    mName("addcontact"),
    mLogin(login)
{
  mStringified = mName + " " + mLogin;
}

AddContactCmd::AddContactCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("addcontact")
{
  if (args.size() < 1)
    return ;
  mLogin = args.front();
  mStringified = mName + " " + mLogin;
}

AddContactCmd::~AddContactCmd()
{
}

void AddContactCmd::exec()
{
  if (Babe::NetworkManager::getSingletonPtr()->sendMessage(mStringified))
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("NetworkManager sended the message \"" + mStringified + "\"");
  else
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("Failed to send the message \"" + mStringified + "\"");
}

std::string const& AddContactCmd::getName() const
{
  return mName;
}

std::string const& AddContactCmd::stringify()
{
  return mStringified;
}

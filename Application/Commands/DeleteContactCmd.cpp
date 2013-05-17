//
// DeleteContactCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 23:25:16 2011 alexandre champion
// Last update Fri Dec  2 21:25:58 2011 alexandre champion
//

#include "DeleteContactCmd.hpp"

DeleteContactCmd::DeleteContactCmd(std::string const& login)
  : Babe::ICommand(LOW),
    mName("deletecontact"),
    mLogin(login)
{
  mStringified = mName + " " + mLogin;
}

DeleteContactCmd::DeleteContactCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("deletecontact")
{
  if (args.size() < 1)
    return ;
  mLogin = args.front();
  mStringified = mName + " " + mLogin;
}

DeleteContactCmd::~DeleteContactCmd()
{
}

void DeleteContactCmd::exec()
{
  if (Babe::NetworkManager::getSingletonPtr()->sendMessage(mStringified))
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("NetworkManager sended the message \"" + mStringified + "\"");
  else
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("Failed to send the message \"" + mStringified + "\"");
}

void DeleteContactCmd::unexec()
{
  Babe::CommandManager::getSingletonPtr()->execute("userstatus " + mLogin + " disconnected");
  Babe::CommandManager::getSingletonPtr()->execute("addcontact " + mLogin);
}

bool DeleteContactCmd::isUndoable() const
{
  return true;
}

std::string const& DeleteContactCmd::getName() const
{
  return mName;
}

std::string const& DeleteContactCmd::stringify()
{
  return mStringified;
}

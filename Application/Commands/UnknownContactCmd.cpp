//
// UnknownContactCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 22:27:04 2011 alexandre champion
// Last update Sun Dec  4 23:00:08 2011 alexandre champion
//

#include "UnknownContactCmd.hpp"

UnknownContactCmd::UnknownContactCmd(std::string const& login)
  : Babe::ICommand(LOW),
    mName("unknowncontact"),
    mLogin(login)
{
  mStringified = mName + " " + mLogin;
}

UnknownContactCmd::UnknownContactCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("unknowncontact")
{
  if (args.size() < 1)
    return ;
  for (Babe::CommandParser::ArgVector::iterator i = args.begin(); i != args.end(); ++i)
    mLogin += (*i) + " ";
  mStringified = mName + " " + mLogin;
}

UnknownContactCmd::~UnknownContactCmd()
{
}

void UnknownContactCmd::exec()
{
  Babe::GuiManager::getSingletonPtr()->notify(mStringified);
  Babe::CommandManager::getSingletonPtr()->setReturnMessage("GuiManager notified \"" + mStringified + "\"");
}

std::string const& UnknownContactCmd::getName() const
{
  return mName;
}

std::string const& UnknownContactCmd::stringify()
{
  return mStringified;
}

//
// EndCallCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Dec  4 18:07:55 2011 alexandre champion
// Last update Sun Dec  4 19:26:41 2011 alexandre champion
//

#include "EndCallCmd.hpp"

EndCallCmd::EndCallCmd(std::string const& login)
  : Babe::ICommand(LOW),
    mName("endcall"),
    mLogin(login)
{
  mStringified = mName + " " + mLogin;
}

EndCallCmd::EndCallCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("endcall")
{
  if (args.size() < 1)
    return ;
  mLogin = args.front();
  mStringified = mName + " " + mLogin;
}

EndCallCmd::~EndCallCmd()
{
}

void EndCallCmd::exec()
{
  Babe::AudioManager::getSingletonPtr()->off();
}

std::string const& EndCallCmd::getName() const
{
  return mName;
}

std::string const& EndCallCmd::stringify()
{
  return mStringified;
}

//
// ResumeCallCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Fri Dec  2 16:54:18 2011 alexandre champion
// Last update Fri Dec  2 17:39:04 2011 alexandre champion
//

#include "ResumeCallCmd.hpp"

ResumeCallCmd::ResumeCallCmd(std::string const& login)
  : Babe::ICommand(LOW),
    mName("resumecall"),
    mLogin(login)
{
  mStringified = mName + " " + mLogin;
}

ResumeCallCmd::ResumeCallCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("resumecall")
{
  if (args.size() < 1)
    return ;
  mLogin = args.front();
  mStringified = mName + " " + mLogin;
}

ResumeCallCmd::~ResumeCallCmd()
{
}

void ResumeCallCmd::exec()
{
  if (Babe::NetworkManager::getSingletonPtr()->sendMessage(mStringified))
    {
      Babe::CommandManager::getSingletonPtr()->setReturnMessage("NetworkManager sended the message \"" + mStringified + "\"");
      Babe::AudioManager::getSingletonPtr()->on();
    }
  else
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("Failed to send the message \"" + mStringified + "\"");
}

std::string const& ResumeCallCmd::getName() const
{
  return mName;
}

std::string const& ResumeCallCmd::stringify()
{
  return mStringified;
}

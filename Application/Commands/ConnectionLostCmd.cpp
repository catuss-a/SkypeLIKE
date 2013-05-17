//
// ConnectionLostCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Dec  4 18:11:29 2011 alexandre champion
// Last update Sun Dec  4 19:26:39 2011 alexandre champion
//

#include "ConnectionLostCmd.hpp"

ConnectionLostCmd::ConnectionLostCmd()
  : Babe::ICommand(LOW),
    mName("connectionlost"),
    mStringified(mName)
{
}

ConnectionLostCmd::ConnectionLostCmd(Babe::CommandParser::ArgVector&)
  : Babe::ICommand(LOW),
    mName("connectionlost"),
    mStringified(mName)
{
}

ConnectionLostCmd::~ConnectionLostCmd()
{
}

void ConnectionLostCmd::exec()
{
  Babe::AudioManager::getSingletonPtr()->off();
  Babe::GuiManager::getSingletonPtr()->notify(mStringified);
  Babe::CommandManager::getSingletonPtr()->setReturnMessage("GuiManager notified \"" + mStringified + "\"");
}

std::string const& ConnectionLostCmd::getName() const
{
  return mName;
}

std::string const& ConnectionLostCmd::stringify()
{
  return mStringified;
}

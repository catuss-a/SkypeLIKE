//
// UserConnectionSucceededCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
//
// Made by alexandre champion
// Login   <champi_d@epitech.net>
//
// Started on  Wed Nov 30 19:08:28 2011 alexandre champion
// Last update Sun Dec  4 11:59:41 2011 alexandre champion
//

#include "UserConnectionSucceededCmd.hpp"

UserConnectionSucceededCmd::UserConnectionSucceededCmd()
  : Babe::ICommand(LOW),
	mName("userconnectionsucceeded"),
	mStringified(mName)
{
}

UserConnectionSucceededCmd::UserConnectionSucceededCmd(Babe::CommandParser::ArgVector&)
  : Babe::ICommand(LOW),
	mName("userconnectionsucceeded"),
	mStringified(mName)
{
}

UserConnectionSucceededCmd::~UserConnectionSucceededCmd()
{
}

void UserConnectionSucceededCmd::exec()
{
  Babe::GuiManager::getSingletonPtr()->notify(mStringified);
  Babe::CommandManager::getSingletonPtr()->setReturnMessage("GuiManager notified \"" + mStringified + "\"");
}

std::string const& UserConnectionSucceededCmd::getName() const
{
  return mName;
}

std::string const& UserConnectionSucceededCmd::stringify()
{
  return mStringified;
}

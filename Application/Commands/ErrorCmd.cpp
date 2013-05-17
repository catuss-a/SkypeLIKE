//
// ErrorCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 23:30:09 2011 alexandre champion
// Last update Sun Dec  4 23:27:24 2011 alexandre champion
//

#include "ErrorCmd.hpp"

ErrorCmd::ErrorCmd(std::string const& errorMessage)
  : Babe::ICommand(LOW),
    mName("error"),
    mErrorMessage(errorMessage),
    mStringified(mName + " " + mErrorMessage)
{
}

ErrorCmd::ErrorCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("error")
{
  if (args.size() < 1)
    return ;
  for (Babe::CommandParser::ArgVector::iterator i = args.begin(); i != args.end(); ++i)
    mErrorMessage += (*i) + " ";
  mStringified = mName + " " + mErrorMessage;
}

ErrorCmd::~ErrorCmd()
{
}

void ErrorCmd::exec()
{
  Babe::GuiManager::getSingletonPtr()->notify(mStringified);
  Babe::CommandManager::getSingletonPtr()->setReturnMessage("GuiManager notified \"" + mStringified + "\"");
}

std::string const& ErrorCmd::getName() const
{
  return mName;
}

std::string const& ErrorCmd::stringify()
{
  return mStringified;
}

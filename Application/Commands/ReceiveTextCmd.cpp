//
// ReceiveTextCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Dec  4 18:22:54 2011 alexandre champion
// Last update Sun Dec  4 18:26:37 2011 alexandre champion
//

#include "ReceiveTextCmd.hpp"

ReceiveTextCmd::ReceiveTextCmd(std::string const& login, std::string const& message)
  : Babe::ICommand(LOW),
    mName("receivetext"),
    mLogin(login),
    mMessage(message),
    mStringified(mName + " " + mLogin + " " + mMessage)
{
}

ReceiveTextCmd::ReceiveTextCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("receivetext")
{
  if (args.size() < 2)
    return ;
  mLogin = args.front();
  args.pop_front();
  for (Babe::CommandParser::ArgVector::iterator i = args.begin(); i != args.end(); ++i)
    mMessage += (*i) + " ";
  mStringified = mName + " " + mLogin + " " + mMessage;
}

ReceiveTextCmd::~ReceiveTextCmd()
{
}

void ReceiveTextCmd::exec()
{
  Babe::GuiManager::getSingletonPtr()->notify(mStringified);
  Babe::CommandManager::getSingletonPtr()->setReturnMessage("GuiManager notified \"" + mStringified + "\"");
}

std::string const& ReceiveTextCmd::getName() const
{
  return mName;
}

std::string const& ReceiveTextCmd::stringify()
{
  return mStringified;
}

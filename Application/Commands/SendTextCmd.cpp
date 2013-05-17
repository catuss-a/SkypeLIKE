//
// SendTextCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Dec  4 18:14:17 2011 alexandre champion
// Last update Sun Dec  4 18:26:30 2011 alexandre champion
//

#include "SendTextCmd.hpp"

SendTextCmd::SendTextCmd(std::string const& login, std::string const& message)
  : Babe::ICommand(LOW),
    mName("sendtext"),
    mLogin(login),
    mMessage(message),
    mStringified(mName + " " + mLogin + " " + mMessage)
{
}

SendTextCmd::SendTextCmd(Babe::CommandParser::ArgVector& args)
  : Babe::ICommand(LOW),
    mName("sendtext")
{
  if (args.size() < 2)
    return ;
  mLogin = args.front();
  args.pop_front();
  for (Babe::CommandParser::ArgVector::iterator i = args.begin(); i != args.end(); ++i)
    mMessage += (*i) + " ";
  mStringified = mName + " " + mLogin + " " + mMessage;
}

SendTextCmd::~SendTextCmd()
{
}

void SendTextCmd::exec()
{
  if (Babe::NetworkManager::getSingletonPtr()->sendMessage(mStringified))
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("NetworkManager sended the message \"" + mStringified + "\"");
  else
    Babe::CommandManager::getSingletonPtr()->setReturnMessage("Failed to send the message \"" + mStringified + "\"");
}

std::string const& SendTextCmd::getName() const
{
  return mName;
}

std::string const& SendTextCmd::stringify()
{
  return mStringified;
}

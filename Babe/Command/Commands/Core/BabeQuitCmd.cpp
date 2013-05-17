//
// BabeQuitCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Babe
//
// Made by alexandre champion
// Login   <champi_d@epitech.net>
//
// Started on  Sun Nov 13 20:54:08 2011 alexandre champion
// Last update Mon Nov 28 18:18:18 2011 alexandre champion
//

#include "BabeQuitCmd.hpp"
#include "BabeApplicationManager.hpp"

namespace Babe
{

  QuitCmd::QuitCmd()
	  : mName("quit")
  {
  }

  QuitCmd::QuitCmd(CommandParser::ArgVector&)
	  : mName("quit")
  {
  }

  void QuitCmd::exec()
  {
    ApplicationManager::getSingletonPtr()->stop();
  }

  std::string const& QuitCmd::getName() const
  {
    return mName;
  }

} // End of namespace Babe

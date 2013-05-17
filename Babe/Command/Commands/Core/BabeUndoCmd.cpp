//
// BabeUndo.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Fri Dec  2 18:11:02 2011 alexandre champion
// Last update Fri Dec  2 18:23:15 2011 alexandre champion
//

#include "BabeUndoCmd.hpp"
#include "BabeApplicationManager.hpp"
#include "BabeCommandManager.hpp"

namespace Babe
{

  UndoCmd::UndoCmd()
    : mName("undo")
  {
  }

  UndoCmd::UndoCmd(CommandParser::ArgVector&)
    : mName("undo")
  {
  }

  UndoCmd::~UndoCmd()
  {
  }

  void UndoCmd::exec()
  {
    if (!CommandManager::getSingletonPtr()->undo())
      CommandManager::getSingletonPtr()->setReturnMessage("Nothing to undo.");
  }

  std::string const& UndoCmd::getName() const
  {
    return mName;
  }

} // End of namespace Babe

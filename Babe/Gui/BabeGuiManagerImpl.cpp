//
// BabeGuiManagerImpl.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Dec  4 18:40:48 2011 alexandre champion
// Last update Sun Dec  4 21:25:42 2011 alexandre champion
//

#include "BabeGuiManagerImpl.hpp"
#include "BabeCommandManager.hpp"

namespace Babe
{

  void GuiManagerDummyImpl::update(float)
  {
    if (!mFirstUpdate)
      {
	LOG("|> No GUI. Here is a console access");
	std::cout << "|> No GUI. Here is a console access" << std::endl;
	mFirstUpdate = true;
      }
    std::string returnMessage = CommandManager::getSingletonPtr()->getReturnMessage();
    if (!returnMessage.empty())
      {
	std::cout << returnMessage << std::endl;
	CommandManager::getSingletonPtr()->setReturnMessage("");
      }
    std::cout << "|> ";
    std::string cmd;
    std::getline(std::cin, cmd, '\n');
    LOG("|> " + cmd);
    if (!cmd.empty())
      CommandManager::getSingletonPtr()->execute(cmd);
  }

} // End of namespace Babe

//
// BabeUnloadPluginCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Dec  4 13:09:12 2011 alexandre champion
// Last update Sun Dec  4 20:57:18 2011 alexandre champion
//

#include "BabeUnloadPluginCmd.hpp"
#include "BabeApplicationManager.hpp"
#include "BabePluginManager.hpp"
#include "BabeCommandManager.hpp"
#include "BabeSystemManager.hpp"

namespace Babe
{

  UnloadPluginCmd::UnloadPluginCmd(std::string const& pluginPath)
    : ICommand(HIGH),
      mName("unloadplugin"),
      mPluginPath(pluginPath)
  {
  }

  UnloadPluginCmd::UnloadPluginCmd(CommandParser::ArgVector& args)
    : ICommand(HIGH),
      mName("unloadplugin")
  {
    if (args.empty())
      return ;
    mPluginPath = args.front();
  }

  void UnloadPluginCmd::exec()
  {

    ////////////
    //return ;
    ////////////

    if (mPluginPath.empty())
      return ;
    Plugin* plugin = PluginManager::getSingletonPtr()->getPluginByFileName(mPluginPath);
    if (plugin)
      {
	std::string pluginName = plugin->getName();
	System* system = SystemManager::getSingletonPtr()->getSystemByName(plugin->getSystemName());
	std::string systemPluginName = system->getPluginName();
	if (pluginName == systemPluginName)
	  {
	    system->shutdown();
	    SystemManager::getSingletonPtr()->unsetSystemImpl(system->getName());
	    CommandManager::getSingletonPtr()->setReturnMessage("Plugin \"" + mPluginPath + "\" unloaded.");
	  }
	else
	  CommandManager::getSingletonPtr()->setReturnMessage("Plugin \"" + mPluginPath + "\" already unloaded.");
      }
    else
      CommandManager::getSingletonPtr()->setReturnMessage("Plugin \"" + mPluginPath + "\" was never loaded");
  }

  std::string const& UnloadPluginCmd::getName() const
  {
    return mName;
  }

  std::string const& UnloadPluginCmd::stringify()
  {
    mStringified = mName + " " + mPluginPath;
    return mStringified;
  }

} // End of namespace Babe

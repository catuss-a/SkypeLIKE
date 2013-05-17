//
// BabeLoadPluginCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d/Babe
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Mon Nov 28 17:26:45 2011 alexandre champion
// Last update Sat Dec  3 15:19:45 2011 alexandre champion
//

#include "BabeLoadPluginCmd.hpp"
#include "BabeApplicationManager.hpp"
#include "BabePluginManager.hpp"
#include "BabeCommandManager.hpp"
#include "BabeSystemManager.hpp"

namespace Babe
{

  LoadPluginCmd::LoadPluginCmd(std::string const& pluginPath)
    : ICommand(HIGH),
      mName("loadplugin"),
      mPluginPath(pluginPath)
  {
  }

  LoadPluginCmd::LoadPluginCmd(CommandParser::ArgVector& args)
    : ICommand(HIGH),
      mName("loadplugin")
  {
    if (args.empty())
      return ;
    mPluginPath = args.front();
  }

  void LoadPluginCmd::exec()
  {
    if (mPluginPath.empty())
      return ;
    Plugin* plugin = PluginManager::getSingletonPtr()->getPluginByFileName(mPluginPath);
    if (!plugin)
      {
	if (PluginManager::getSingletonPtr()->loadPlugin(mPluginPath))
	  {
	    Plugin* plugin = PluginManager::getSingletonPtr()->getPluginByFileName(mPluginPath);
	    System* system = SystemManager::getSingletonPtr()->getSystemByName(plugin->getSystemName());
	    system->shutdown();
	    if (!plugin->initialize())
	      {
		LOGE("Couldn't initialise the plugin '" + plugin->getName() + "'");
		CommandManager::getSingletonPtr()->setReturnMessage("Plugin \"" + mPluginPath + "\" failed : Couldn't initialise the plugin '" + plugin->getName() + "'");
		return ;
	      }
	    system->init();
	    CommandManager::getSingletonPtr()->setReturnMessage("Plugin \"" + mPluginPath + "\" loaded");
	  }
	else
	  CommandManager::getSingletonPtr()->setReturnMessage("Failed to load plugin \"" + mPluginPath + "\"");
      }
    else
      {
	std::string pluginName = plugin->getName();
	System* system = SystemManager::getSingletonPtr()->getSystemByName(plugin->getSystemName());
	std::string systemPluginName = system->getPluginName();
	if (pluginName != systemPluginName)
	  {
	    system->shutdown();
	    if (!plugin->initialize())
	      {
		LOGE("Couldn't initialise the plugin '" + plugin->getName() + "'");
		CommandManager::getSingletonPtr()->setReturnMessage("Couldn't initialise the plugin '" + plugin->getName() + "'");
		return ;
	      }
	    system->init();
	    CommandManager::getSingletonPtr()->setReturnMessage("Plugin \"" + mPluginPath + "\" loaded. System " + system->getName() + " initialized.");
	  }
	else
	  CommandManager::getSingletonPtr()->setReturnMessage("Plugin \"" + mPluginPath + "\" already loaded.");
      }
  }

  std::string const& LoadPluginCmd::getName() const
  {
    return mName;
  }

  std::string const& LoadPluginCmd::stringify()
  {
    mStringified = mName + " " + mPluginPath;
    return mStringified;
  }

} // End of namespace Babe

//
// BabePluginManagerPosixImpl.cpp for  in /home/champi_d//AdvancedCPP/Babel
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Tue Nov 15 18:16:43 2011 alexandre champion
// Last update Sat Dec  3 15:33:43 2011 alexandre champion
//

#include <string>
#include <dlfcn.h>
#include "BabeLogManager.hpp"
#include "BabePluginManagerPosixImpl.hpp"

namespace Babe
{

  PluginManagerPosixImpl::PluginManagerPosixImpl()
  {
    LOG("PluginManagerPosixImpl created");
  }

  PluginManagerPosixImpl::~PluginManagerPosixImpl()
  {
    LOG("Destroying PluginManagerPosixImpl...");
  }

  void		PluginManagerPosixImpl::callDlError(std::string const& where)
  {
    std::string errorString;
    std::string error;
    const char *errorCode = dlerror();
    if (errorCode)
      error = errorCode;
    errorString = where + " ";
    if(error.size())
      errorString += error;
    LOGE(errorString);
  }

  bool		PluginManagerPosixImpl::loadPlugin(std::string const& filename)
  {
    std::string fileName = "lib" + filename + ".so";
    LOG("Loading plugin: '" + fileName + "'");
    void* dlHandle = dlopen(fileName.c_str(), RTLD_NOW);
    if (!dlHandle)
      {
	callDlError("dlopen");
	return false;
      }
    convertPtr ptr;
    ptr.objPtr = dlsym(dlHandle, "registerPlugin");
    if (!ptr.registerFct)
      {
	callDlError("dlsym : No entry point 'RegisterPlugin'?");
	return false;
      }
    if (!ptr.registerFct(this, dlHandle))
      {
	LOGE("Error while trying to register the plugin");
	dlclose(dlHandle);
	return false;
      }
    mPluginsByFileName[filename] = mCurrentParam;
    return true;
  }

  bool		PluginManagerPosixImpl::pluginValidityCheck(PluginParams* params)
  {
    if (params->systemName.empty() || params->pluginName.empty())
      return false;
    if (!params->createFct || !params->destroyFct)
      return false;
    return true;
  }

  bool		PluginManagerPosixImpl::registerPlugin(PluginParams* params)
  {
    if (!pluginValidityCheck(params))
      return false;
    Plugin* plugin = params->createFct();
    plugin->init(params->systemName, params->pluginName, params->version);
    if (!plugin)
      {
	LOGE("Error while trying to create an instance of the plugin " + params->pluginName);
	return false;
      }
    params->plugin = plugin;
    mPlugins[params->pluginName] = *params;
    mCurrentParam = *params;
    LOG(params->pluginName + " plugin registered.");
    return true;
  }

  bool		PluginManagerPosixImpl::unloadPlugin(std::string const& name)
  {
    PluginMap::iterator i = mPlugins.find(name);
    if (i == mPlugins.end())
      return false;
    PluginParams* params = &i->second;
    try
      {
	if (params->destroyFct && params->plugin)
	  params->destroyFct(params->plugin);
	else
	  LOGE("No destroy fct or plugin instance in " + i->first);
	if (params->dlHandle)
	  dlclose(params->dlHandle);
      }
    catch(...)
      {
	LOGE("Uncaught exception unloading plugin: " + i->first);
	if (params->dlHandle)
	  dlclose(params->dlHandle);
      }    
    LOG("Plugin " + i->first + " unloaded");
    return true;
  }
  
  void		PluginManagerPosixImpl::unloadAll()
  {
    LOG("PluginManagerPosixImpl : Unloading all of the plugins.");
    PluginMap::iterator iter;
    for (iter = mPlugins.begin(); iter != mPlugins.end(); iter++)
      {
		unloadPlugin(iter->first);
      }
    mPlugins.clear();
  }

  Plugin*	PluginManagerPosixImpl::getPlugin(std::string const& name)
  {
    PluginMap::iterator iter = mPlugins.find(name);
    if (iter == mPlugins.end())
      return 0;
    return iter->second.plugin; 
  }

  Plugin*	PluginManagerPosixImpl::getPluginByFileName(std::string const& name)
  {
    PluginMap::iterator iter = mPluginsByFileName.find(name);
    if (iter == mPluginsByFileName.end())
      return 0;
    return iter->second.plugin; 
  }

  bool		PluginManagerPosixImpl::initializePlugin(std::string const& name)
  {
    LOG("PluginManagerPosixImpl::initializePlugin(\"" + name + "\");");
    Plugin* plugin = getPlugin(name);
    if (!plugin)
      {
	LOGE("Couldn't find the plugin '" + name + "'");
	return false;
      }
    if (!plugin->initialize())
      {
	LOGE("Couldn't initialise the plugin '" + name + "'");
	return false;
      }
    LOG(name + " plugin initialized.");
    return true; 
  }

} // End of namespace Babe

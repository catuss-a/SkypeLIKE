//
// BabePluginManagerWin32Impl.cpp
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 

#include <string>
#include <Windows.h>
#include "BabeLogManager.hpp"
#include "BabePluginManagerWin32Impl.hpp"

namespace Babe
{

	template <> PluginManagerWin32Impl* Singleton<PluginManagerWin32Impl>::msSingleton = 0;

  PluginManagerWin32Impl::PluginManagerWin32Impl()
  {
    LOG("PluginManagerWin32Impl created");
  }

  PluginManagerWin32Impl::~PluginManagerWin32Impl()
  {
    LOG("Destroying PluginManagerWin32Impl...");
  }

  void		PluginManagerWin32Impl::callDlError(std::string const& where)
  {
	  LOGE("TO IMPLEMENT : PluginManagerWin32Impl::callDlError " + where);
	  DWORD error = GetLastError();
  }

  bool		PluginManagerWin32Impl::loadPlugin(std::string const& filename)
  {
	  std::string fileName = filename + ".dll";
	  LOG("Loading plugin: '" + fileName + "'");
	  HMODULE dlHandle = LoadLibraryA(fileName.c_str());
	  if (!dlHandle)
	  {
		callDlError("LoadLibraryA");
		return false;
	  }
	  convertPtr ptr;
	  ptr.objPtr = GetProcAddress(dlHandle, "registerPlugin");
	  if (!ptr.registerFct)
      {
		callDlError("GetProcAddress : No entry point 'RegisterPlugin'?");
		return false;
      }
	  if (!ptr.registerFct(this, dlHandle))
      {
		LOGE("Error while trying to register the plugin");
		FreeLibrary((HMODULE)dlHandle);
		return false;
      }
	  mPluginsByFileName[filename] = mCurrentParam;
	  return true;
  }

  bool		PluginManagerWin32Impl::pluginValidityCheck(PluginParams* params)
  {
    if (params->systemName.empty() || params->pluginName.empty())
      return false;
    if (!params->createFct || !params->destroyFct)
      return false;
    return true;
  }

  bool		PluginManagerWin32Impl::registerPlugin(PluginParams* params)
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

  bool		PluginManagerWin32Impl::unloadPlugin(std::string const& name)
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
			FreeLibrary((HMODULE)params->dlHandle);
      }
    catch(...)
      {
		  LOGE("Uncaught exception unloading plugin: " + i->first);
		  if (params->dlHandle)
			  FreeLibrary((HMODULE)params->dlHandle);
      }
	LOG("Plugin " + i->first + " unloaded");
    return true;
  }
  
  void		PluginManagerWin32Impl::unloadAll()
  {
    LOG("PluginManagerWin32Impl : Unloading all of the plugins.");
    PluginMap::iterator iter;
    for (iter = mPlugins.begin(); iter != mPlugins.end(); iter++)
      {
		  unloadPlugin(iter->first);
      }
    mPlugins.clear();
  }

  Plugin*	PluginManagerWin32Impl::getPlugin(std::string const& name)
  {
    PluginMap::iterator iter = mPlugins.find(name);
    if (iter == mPlugins.end())
      return 0;
    return iter->second.plugin;
  }

  Plugin*	PluginManagerWin32Impl::getPluginByFileName(std::string const& name)
  {
    PluginMap::iterator iter = mPluginsByFileName.find(name);
    if (iter == mPluginsByFileName.end())
      return 0;
    return iter->second.plugin;
  }

  bool		PluginManagerWin32Impl::initializePlugin(std::string const& name)
  {
    LOG("PluginManagerWin32Impl::initializePlugin(\"" + name + "\");");
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

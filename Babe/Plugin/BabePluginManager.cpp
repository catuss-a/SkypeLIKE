
#include <string>
#include "BabeLogManager.hpp"
#include "BabePluginManager.hpp"
#include "BabeDef.hpp"
#if defined (BABE_UNIX)
# include "BabePluginManagerPosixImpl.hpp"
#else
# include "BabePluginManagerWin32Impl.hpp"
#endif // ! BABE_UNIX

namespace Babe
{
	PluginManager* PluginManager::getSingletonPtr()
	{
		return msSingleton;
	}

	PluginManager& PluginManager::getSingleton()
	{
        ASSERT_SINGLETON( msSingleton, "PluginManager", "getSingleton()" );  return ( *msSingleton );  
	}

	PluginManager::PluginManager()
  {
    LOG("PluginManager created");
#if defined (BABE_UNIX)
    mImpl = new PluginManagerPosixImpl;
#else
    mImpl = new PluginManagerWin32Impl;
#endif // ! BABE_UNIX
  }

  PluginManager::~PluginManager()
  {
    LOG("Destroying PluginManager...");
  }

  bool		PluginManager::loadPlugin(std::string const& fileName)
  {
    if (mLoadedPlugins.find(fileName) != mLoadedPlugins.end())
      return true;
    if (mLoadFailedPlugins.find(fileName) != mLoadFailedPlugins.end())
      return false;
    bool pluginLoaded = mImpl->loadPlugin(fileName);
    if (pluginLoaded)
      mLoadedPlugins[fileName] = fileName;
    else
      mLoadFailedPlugins[fileName] = fileName;
    return pluginLoaded;
  }

  bool		PluginManager::unloadPlugin(std::string const& pluginName)
  {
    return mImpl->unloadPlugin(pluginName);
  }
  
  void		PluginManager::unloadAll()
  {
    mImpl->unloadAll();
  }

  Plugin*	PluginManager::getPlugin(std::string const& pluginName)
  {
    return mImpl->getPlugin(pluginName);
  }

  Plugin*	PluginManager::getPluginByFileName(std::string const& fileName)
  {
    return mImpl->getPluginByFileName(fileName);
  }

  bool		PluginManager::initializePlugin(std::string const& pluginName)
  {
    return mImpl->initializePlugin(pluginName);
  }

} // End of namespace Babe

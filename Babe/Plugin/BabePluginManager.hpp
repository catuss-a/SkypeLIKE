
#ifndef		__BABE_PLUGINMANAGER_HPP__
# define	__BABE_PLUGINMANAGER_HPP__

# include <string>
# include <map>
# include "BabeDef.hpp"
# include "BabeSingleton.hpp"
# include "BabePlugin.hpp"
# include "BabePluginManagerImpl.hpp"

namespace Babe
{

  class BABE_DLLREQ PluginManager : public Singleton<PluginManager>
  {
  public:
    PluginManager();
    ~PluginManager();
    bool loadPlugin(std::string const& fileName);
    bool unloadPlugin(std::string const& pluginName);
    void unloadAll();
    Plugin* getPlugin(std::string const& pluginName);
    Plugin* getPluginByFileName(std::string const& fileName);
    bool initializePlugin(std::string const& pluginName);
    static PluginManager* getSingletonPtr();
    static PluginManager& getSingleton();
    
  private:
    typedef std::map<std::string, std::string> LoadedPluginMap;
    PluginManagerImpl* mImpl;
    LoadedPluginMap mLoadedPlugins;
    LoadedPluginMap mLoadFailedPlugins;
  };

} // End of namespace Babe

#endif		// ! __BABE_PLUGINMANAGER_HPP__

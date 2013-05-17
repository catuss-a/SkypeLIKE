
#ifndef		__BABE_PLUGINMANAGERIMPL_HPP__
# define	__BABE_PLUGINMANAGERIMPL_HPP__

# include <map>
# include "BabeDef.hpp"

namespace Babe
{

  class BABE_DLLREQ PluginManagerImpl
  {
  public:
    typedef bool	(*RegisterPlugin)(PluginManagerImpl*, void*);
    union convertPtr
    {
      void*		objPtr;
      RegisterPlugin	registerFct;
    };
    typedef Plugin*	(*PluginCreate)();
    typedef bool	(*PluginDestroy)(Plugin*);
    struct PluginParams
    {
      void*		dlHandle;
      PluginCreate	createFct;
      PluginDestroy	destroyFct;
      std::string	systemName;
      std::string	pluginName;
      std::string	version;
      Plugin*		plugin;
    };

  public:
    virtual ~PluginManagerImpl() {}
    virtual bool loadPlugin(std::string const& filename) = 0;
    virtual bool pluginValidityCheck(PluginParams* params) = 0;
    virtual bool registerPlugin(PluginParams* params) = 0;
    virtual bool unloadPlugin(std::string const& name) = 0;
    virtual void unloadAll() = 0;
    virtual Plugin* getPlugin(std::string const& name) = 0; 
    virtual Plugin* getPluginByFileName(std::string const& fileName) = 0; 
    virtual bool initializePlugin(std::string const& name) = 0;
  
  protected:
    typedef std::map<std::string, PluginParams> PluginMap;
    PluginMap		mPlugins;
    PluginMap		mPluginsByFileName;
    PluginParams	mCurrentParam;
  };

} // End of namespace Babe

#endif		// ! __BABE_PLUGINMANAGERIMPL_HPP__

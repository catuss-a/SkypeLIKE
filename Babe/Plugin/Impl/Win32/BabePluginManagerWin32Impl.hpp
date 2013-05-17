//
// BabePluginManagerWin32Impl.hpp for  in /home/champi_d//AdvancedCPP/Babel
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Tue Nov 15 18:11:29 2011 alexandre champion
// Last update Thu Nov 17 17:18:40 2011 alexandre champion
//

#ifndef		__BABE_PLUGINMANAGERWIN32IMPL_HPP__
# define	__BABE_PLUGINMANAGERWIN32IMPL_HPP__

# include <string>
# include <map>
# include "BabeSingleton.hpp"
# include "BabePlugin.hpp"
# include "BabePluginManagerImpl.hpp"

namespace Babe
{

  class PluginManagerWin32Impl : public PluginManagerImpl, public Singleton<PluginManagerWin32Impl>
  {
  public:
    PluginManagerWin32Impl();
    virtual ~PluginManagerWin32Impl();
    virtual bool loadPlugin(std::string const& filename);
    virtual bool pluginValidityCheck(PluginParams* params);
    virtual bool registerPlugin(PluginParams* params); 
    virtual bool unloadPlugin(std::string const& name);
    virtual void unloadAll();
    virtual Plugin* getPlugin(std::string const& name);
	virtual Plugin* getPluginByFileName(std::string const& fileName);
    virtual bool initializePlugin(std::string const& name);

  private:
    void callDlError(std::string const& where);
  };

} // End of namespace Babe

#endif		// ! __BABE_PLUGINMANAGERWIN32IMPL_HPP__

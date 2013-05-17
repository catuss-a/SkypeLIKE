//
// NetworkPluginNina.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Mon Nov 28 22:56:12 2011 alexandre champion
// Last update Mon Nov 28 22:57:16 2011 alexandre champion
//

#include <Babe.hpp>
#include "NetworkManagerNinaImpl.hpp"

typedef Babe::PluginTpl<NetworkManagerNinaImpl> NetworkPluginNina;

extern "C"
{
  BABE_DLLREQ bool registerPlugin(Babe::PluginManagerImpl* pluginManager, void* dlHandle)
  {
    Babe::PluginManagerImpl::PluginParams pp;
    pp.dlHandle = dlHandle;
    pp.createFct = &NetworkPluginNina::createInstance;
    pp.destroyFct = &NetworkPluginNina::destroyInstance;
    pp.systemName = "NetworkSystem";
    pp.pluginName = "NetworkPluginNina";
    pp.version = "0.0";
    if (!pluginManager->registerPlugin(&pp))
      return false;
    return true;
  }
}

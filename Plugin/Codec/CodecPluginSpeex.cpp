
#include <Babe.hpp>
#include "CodecManagerSpeexImpl.hpp"

typedef Babe::PluginTpl<CodecManagerSpeexImpl> CodecPluginSpeex;

extern "C"
{
  BABE_DLLREQ bool registerPlugin(Babe::PluginManagerImpl* pluginManager, void* dlHandle)
  {
    Babe::PluginManagerImpl::PluginParams pp;
    pp.dlHandle = dlHandle;
    pp.createFct = &CodecPluginSpeex::createInstance;
    pp.destroyFct = &CodecPluginSpeex::destroyInstance;
    pp.systemName = "CodecSystem";
    pp.pluginName = "CodecPluginSpeex";
    pp.version = "0.0";
    if (!pluginManager->registerPlugin(&pp))
      return false;
    return true;
  }
}

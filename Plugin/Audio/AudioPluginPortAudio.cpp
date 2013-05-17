
#include <Babe.hpp>
#include "AudioManagerPortAudioImpl.hpp"

typedef Babe::PluginTpl<AudioManagerPortAudioImpl> AudioPluginPortAudio;

extern "C"
{
  BABE_DLLREQ bool registerPlugin(Babe::PluginManagerImpl* pluginManager, void* dlHandle)
  {
    Babe::PluginManagerImpl::PluginParams pp;
    pp.dlHandle = dlHandle;
    pp.createFct = &AudioPluginPortAudio::createInstance;
    pp.destroyFct = &AudioPluginPortAudio::destroyInstance;
    pp.systemName = "AudioSystem";
    pp.pluginName = "AudioPluginPortAudio";
    pp.version = "0.0";
    if (!pluginManager->registerPlugin(&pp))
      return false;
    return true;
  }
}


#include "BabeSystemFactories.hpp"
#include "BabeLogManager.hpp"

#include "BabeAudioManager.hpp"
#include "BabeGuiManager.hpp"
#include "BabeNetworkManager.hpp"
#include "BabeCodecManager.hpp"

namespace Babe
{

  SystemFactories::SystemFactories()
  {
    mFactories["AudioSystem"] = new SystemFactoryTpl<AudioManager>;
    mFactories["GuiSystem"] = new SystemFactoryTpl<GuiManager>;
    mFactories["NetworkSystem"] = new SystemFactoryTpl<NetworkManager>;
    mFactories["CodecSystem"] = new SystemFactoryTpl<CodecManager>;
  }

  SystemFactories::~SystemFactories()
  {
    for (SystemFactoryMap::iterator i = mFactories.begin(); i != mFactories.end(); ++i)
      delete i->second;
  }

  System* SystemFactories::createSystem(std::string const& systemName)
  {
    SystemFactoryMap::iterator found = mFactories.find(systemName);
    if (found != mFactories.end())
      return found->second->createSystem();
    LOGE("System \"" + systemName + "\" not found");
    return 0;
  }

} // End of namespace Babe

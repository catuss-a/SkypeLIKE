
#include "BabePlugin.hpp"
#include "BabeSystemManager.hpp"

namespace Babe
{

  Plugin::Plugin(std::string systemName, std::string version, SystemImplFactory* factory)
    : mSystemName(systemName),
      mVersion(version),
      mFactory(factory),
      mManagerImpl(0),
      mIsInit(false)
  {
  }

  Plugin::Plugin(SystemImplFactory* factory)
    : mFactory(factory),
      mManagerImpl(0),
      mIsInit(false)
  {
  }

  Plugin::~Plugin()
  {
    shutdown();
  }

  void			Plugin::init(std::string const& systemName, std::string const& pluginName, std::string const& version)
  {
    mSystemName = systemName;
    mPluginName = pluginName;
    mVersion = version;
  }

  std::string const&	Plugin::getName() const
  {
    return mPluginName;
  }

  std::string const&	Plugin::getSystemName() const
  {
    return mSystemName;
  }

  std::string const&	Plugin::getVersion() const
  {
    return mVersion;
  }

  bool			Plugin::initialize()
  {
    if (!mIsInit)
      {
	mIsInit = true;
	mManagerImpl = mFactory->createSystemImpl();
      }
    SystemManager::getSingletonPtr()->setSystemImpl(mSystemName, mPluginName, mManagerImpl);
    return true;
  }

  bool			Plugin::shutdown()
  {
    // we should set the system back to a dummy impl
    SystemManager::getSingletonPtr()->unsetSystemImpl(mSystemName);
    // destroy mManager
    delete mFactory;
    delete mManagerImpl;
    return true;
  }

} // End of namespace Babe

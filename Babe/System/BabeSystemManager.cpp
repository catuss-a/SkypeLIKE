
#include "BabeSystemManager.hpp"
#include "BabeApplicationUpdateHandler.hpp"
#include "BabeLogManager.hpp"

namespace Babe
{
  SystemManager* SystemManager::getSingletonPtr()
  {
    return msSingleton;
  }

  SystemManager& SystemManager::getSingleton()
  {
    ASSERT_SINGLETON( msSingleton, "SystemManager", "getSingleton()" );  return ( *msSingleton );
  }

  SystemManager::SystemManager()
    : mFactories(new SystemFactories)
  {
  }

  SystemManager::~SystemManager()
  {
    delete mFactories;
  }

  System*	SystemManager::createSystem(std::string const& systemName)
  {
    return mFactories->createSystem(systemName);
  }

  bool		SystemManager::registerSystem(System* system)
  {
    if (!system)
      return false;
    SystemMap::iterator iter = mSystems.find(system->getName());
    if (iter != mSystems.end())
      return false;
    mSystems[system->getName()] = system;
    LOG(system->getName() + " registered to the SystemManager");
    return true;
  }

  bool		SystemManager::unregisterSystem(System* system)
  {
    SystemMap::iterator iter = mSystems.find(system->getName());
    if (iter == mSystems.end())
      return false;
    mSystems.erase(iter);
    LOG(system->getName() + " unregistered to the SystemManager");
    return true;
  }

  void		SystemManager::registerSystemsToUpdate()
  {
    int currentRunOrdering = 0;
    int	tmp = 0;
    int maxRunOrdering = 0;
    for (SystemMap::iterator i = mSystems.begin(); i != mSystems.end(); ++i)
      if (maxRunOrdering < i->second->getRunOrdering())
	maxRunOrdering = i->second->getRunOrdering();
    while (currentRunOrdering < maxRunOrdering + 1)
      {
	tmp = currentRunOrdering;
	for (SystemMap::iterator i = mSystems.begin(); i != mSystems.end(); ++i)
	  {
	    if (i->second->getRunOrdering() == currentRunOrdering)
	      {
		ApplicationUpdateHandler::getSingletonPtr()->registerSystem(i->second);
		++currentRunOrdering;
	      }
	  }
	if (tmp == currentRunOrdering)
	  ++currentRunOrdering;
      }
    for (SystemMap::iterator i = mSystems.begin(); i != mSystems.end(); ++i)
      if (i->second->getRunOrdering() == -1)
	ApplicationUpdateHandler::getSingletonPtr()->registerSystem(i->second);
  }

  bool		SystemManager::initSystems()
  {
    int currentInitOrdering = 0;
    int	tmp = 0;
    int maxInitOrdering = 0;
    for (SystemMap::iterator i = mSystems.begin(); i != mSystems.end(); ++i)
      if (maxInitOrdering < i->second->getInitOrdering())
	maxInitOrdering = i->second->getInitOrdering();
    while (currentInitOrdering < maxInitOrdering + 1)
      {
	tmp = currentInitOrdering;
	for (SystemMap::iterator i = mSystems.begin(); i != mSystems.end(); ++i)
	  {
	    if (i->second->getInitOrdering() == currentInitOrdering)
	      {
		if (!i->second->init())
		  {
		    LOGE("Cannot init " + i->second->getName());
		    return false;
		  }
		++currentInitOrdering;
	      }
	  }
	if (tmp == currentInitOrdering)
	  ++currentInitOrdering;
      }
    for (SystemMap::iterator i = mSystems.begin(); i != mSystems.end(); ++i)
      if (i->second->getInitOrdering() == -1)
	{
	  if (!i->second->init())
	    {
	      LOGE("Cannot init " + i->second->getName());
	      return false;
	    }
	}
    return true;
  }

  void		SystemManager::shutdownSystems()
  {
    for (SystemMap::iterator i = mSystems.begin(); i != mSystems.end(); ++i)
      i->second->shutdown();
  }

  System*	SystemManager::getSystemByName(std::string const& name)
  {
    SystemMap::iterator iter = mSystems.find(name);
    if (iter == mSystems.end())
      return 0;
    return iter->second;
  }

  void		SystemManager::setSystemImpl(std::string const& systemName, std::string const& pluginName, SystemImpl* impl)
  {
    LOG("SystemManager::setSystemImpl(\"" + systemName +"\", impl);");
    System* system = getSystemByName(systemName);
    if (!system)
      return ;
    system->setPluginName(pluginName);
    system->setImpl(impl);
  }

  void		SystemManager::unsetSystemImpl(std::string const& systemName)
  {
    System* system = getSystemByName(systemName);
    if (!system)
      return ;
    system->setPluginName("dummy");
    system->unsetImpl();
  }

} // End of namespace Babe

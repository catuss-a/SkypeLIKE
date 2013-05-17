
#include "BabeApplicationManager.hpp"
#include "BabeStringUtils.hpp"

namespace Babe
{
	ApplicationManager* ApplicationManager::getSingletonPtr()
	{
		return msSingleton;
	}

	ApplicationManager& ApplicationManager::getSingleton()
	{
		ASSERT_SINGLETON( msSingleton, "ApplicationManager", "getSingleton()" );  return ( *msSingleton );
	}

  ApplicationManager::ApplicationManager(std::string const& name, std::string const& prefixPath)
    : mApplicationName(name),
      mInitialised(false),
      mCanBeInit(true),
      mPluginsLoaded(false)
  {
    mLog = new LogManager(name);
    LOG("ApplicationManager created");
    mSettings = new ApplicationSettings(name, prefixPath);
    mUpdateHandler = new ApplicationUpdateHandler;
    mSystemMgr = new SystemManager;
    mPlugMgr = new PluginManager;
    mCmdMgr = new CommandManager;
    if (!mSettings->getEntries())
      {
	LOGE("Cannot run the Application without a config file!!! The config file should be named " +
	     mSettings->getConfigFileName());
	mCanBeInit = false;
      }
  }

  ApplicationManager::~ApplicationManager()
  {
    LOG("Destroying ApplicationManager...");
    delete mPlugMgr;
    delete mSystemMgr;
    delete mUpdateHandler;
    delete mSettings;
    delete mCmdMgr;
    delete mLog;
  }

  bool		ApplicationManager::init()
  {
    if (mInitialised)
      return true;
    LOG("Initializing ApplicationManager");
    if (!mCanBeInit)
      return false;
    if (!mPluginsLoaded)
      loadPlugins();
    setupSystems();
    mInitialised = initSystems();
    if (!mInitialised)
      return mInitialised;
    mInitialised = loadAssets();
    return mInitialised;
  }

  void		ApplicationManager::loadPlugins()
  {
    LOG("\n\n\n/-----------------------------------Loading Plugins---------------------------------\\");
    for (ApplicationSettings::SystemEntriesVector::iterator i = mSettings->mSystemEntries.begin();
	 i != mSettings->mSystemEntries.end(); ++i)
      {
	if (i->isPlugin)
	  {
	    LOG("\nmPlugManager->loadPlugin(" + i->pluginPath + ");");
	    if (!mPlugMgr->loadPlugin(i->pluginPath))
	      {
		mPluginsLoaded = false;
		LOGE("ApplicationManager::loadPlugins " + i->pluginPath + " failed");
	      }
	  }
      }
    LOG("\n\\------------------------------------Plugins loaded---------------------------------/\n\n\n\n");
    mPluginsLoaded = true;
  }

  void		ApplicationManager::setupSystems()
  {
    createAndRegisterSystems();
    setSystemsImpl();
    setSystemsSettings();
    registerSystemsToUpdate();
  }


  void		ApplicationManager::createAndRegisterSystems()
  {
    LOG("\n/-----------------Creating and Registering Systems to SystemManager-----------------\\\n");
    LOG("--Builtin systems--");
    mSystemMgr->registerSystem(mCmdMgr);
    LOG("--End of Builtin systems--");
    System* system;
    for (ApplicationSettings::SystemEntriesVector::iterator i = mSettings->mSystemEntries.begin();
	 i != mSettings->mSystemEntries.end(); ++i)
      {
	system = mSystemMgr->createSystem(i->systemName);
	mSystemMgr->registerSystem(system);
      }
    LOG("\n\\------------------Systems Created and Registered to SystemManager------------------/\n\n\n\n");
  }

  void		ApplicationManager::setSystemsImpl()
  {
    LOG("\n/---------------------Setting Implementation for Plugin Systems---------------------\\");
    for (ApplicationSettings::SystemEntriesVector::iterator i = mSettings->mSystemEntries.begin();
	 i != mSettings->mSystemEntries.end(); ++i)
      {
	if (i->isPlugin)
	  {
	    LOG("\nmPlugManager->initializePlugin(" + i->pluginName + ");");
	    if (!mPlugMgr->initializePlugin(i->pluginName))
	      LOGE(i->pluginName + " not found");
	  }
      }
    LOG("\n\\--------------------Implementation of Plugin Systems Are Now Set-------------------/\n\n\n\n");
  }

  void		ApplicationManager::setSystemsSettings()
  {
    System* system;
    for (ApplicationSettings::SystemEntriesVector::iterator i = mSettings->mSystemEntries.begin();
	 i != mSettings->mSystemEntries.end(); ++i)
      {
	system = mSystemMgr->getSystemByName(i->systemName);
	if (system)
	  {
	    system->setInitOrdering(i->initOrdering);
	    system->setRunOrdering(i->runOrdering);
	    system->setTargetRate(i->targetRate);
	  }
	else
	  LOGE(i->systemName + " does not exist");
      }
  }

  void		ApplicationManager::registerSystemsToUpdate()
  {
    LOG("\n/------------------Registering Systems to ApplicationUpdateHandler------------------\\\n");
    mSystemMgr->registerSystemsToUpdate();
    LOG("\n\\-------------------Systems Registered to ApplicationUpdateHandler------------------/\n\n\n\n");
  }

  bool		ApplicationManager::initSystems()
  {
    LOG("\n/--------------------------------Initializing Systems-------------------------------\\\n");
    bool init = mSystemMgr->initSystems();
    if (init)
      LOG("\n\\--------------------------------Systems Initialized--------------------------------/\n\n\n\n");
    else
      {
	LOG("\n>>>>>>>>>>>>>>>>>>>>>>>>>>Could not initialize Systems<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
	LOGE("\n>>>>>>>>>>>>>>>>>>>>>>>>>>Could not initialize Systems<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
      }
    return init;
  }

  bool		ApplicationManager::loadAssets()
  {
    LOG("\n/-----------------------------------Loading Assets----------------------------------\\\n");
    LOG("\n\\-----------------------------------Assets loaded-----------------------------------/\n\n\n\n");
    return true;
  }

  bool		ApplicationManager::run()
  {
    if (!mInitialised)
      init();
    LOG("**************************[ The engine has started running ]*************************\n");
    mUpdateHandler->run();
    LOG("\n**************************[ The engine has stopped running ]*************************\n\n\n\n");
    mPlugMgr->unloadAll();
    return true;
  }

  bool		ApplicationManager::stop()
  {
    if (mInitialised && mUpdateHandler)
      return mUpdateHandler->stop();
    return false;
  }

  std::string const& ApplicationManager::getApplicationName() const
  {
    return mApplicationName;
  }

} // End of namespace Babe


#ifndef		__BABE_APPLICATIONMANAGER_HPP__
# define	__BABE_APPLICATIONMANAGER_HPP__

# include <string>
# include "BabeDef.hpp"
# include "BabeSingleton.hpp"
# include "BabeLogManager.hpp"
# include "BabeApplicationUpdateHandler.hpp"
# include "BabeSystemManager.hpp"
# include "BabeApplicationSettings.hpp"
# include "BabePluginManager.hpp"
# include "BabeCommandManager.hpp"

namespace Babe
{

  class BABE_DLLREQ ApplicationManager : public Singleton<ApplicationManager>
  {
  public:
    ApplicationManager(std::string const& name, std::string const& prefixPath = "");
    ~ApplicationManager();
    void loadPlugins();
    bool init();
    bool run();
    bool stop();
    std::string const& getApplicationName() const;
	static ApplicationManager* getSingletonPtr();
	static ApplicationManager& getSingleton();

  private:
    void setupSystems();
    void createAndRegisterSystems();
    void setSystemsImpl();
    void setSystemsSettings();
    void registerSystemsToUpdate();
    bool initSystems();
    bool loadAssets();

  private:
    std::string			mApplicationName;
    bool			mInitialised;
    bool			mCanBeInit;
    bool			mPluginsLoaded;
    LogManager*			mLog;
    ApplicationSettings*       	mSettings;
    ApplicationUpdateHandler*	mUpdateHandler;
    SystemManager*		mSystemMgr;
    PluginManager*		mPlugMgr;
    CommandManager*		mCmdMgr;
  };
} // End of namespace Babe

#endif		// ! __BABE_APPLICATIONMANAGER_HPP__

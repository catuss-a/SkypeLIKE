
#ifndef		__BABE_SYSTEMMANAGER_HPP__
# define	__BABE_SYSTEMMANAGER_HPP__

# include <map>
# include <string>
# include "BabeDef.hpp"
# include "BabeSingleton.hpp"
# include "BabeSystem.hpp"
# include "BabeSystemImpl.hpp"
# include "BabeSystemFactories.hpp"

namespace Babe
{

  class BABE_DLLREQ SystemManager : public Singleton<SystemManager>
  {
  public:
    SystemManager();
    virtual ~SystemManager();
    System* createSystem(std::string const& systemName);
    bool registerSystem(System* system);
    bool unregisterSystem(System* system);
    void registerSystemsToUpdate();
    bool initSystems();
    void shutdownSystems();
    System* getSystemByName(std::string const& systemName);
    void setSystemImpl(std::string const& systemName, std::string const& pluginName, SystemImpl* impl);
    void unsetSystemImpl(std::string const& systemName);
	static SystemManager* getSingletonPtr();
	static SystemManager& getSingleton();

  private:
    typedef std::map<std::string, System*> SystemMap;
    SystemMap		mSystems;
    SystemFactories*	mFactories;
  };

} // End of namespace Babe

#endif		// ! __BABE_SYSTEMMANAGER_HPP__

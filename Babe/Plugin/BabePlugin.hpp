
#ifndef		__BABE_PLUGIN_HPP__
# define	__BABE_PLUGIN_HPP__

# include <string>
# include "BabeDef.hpp"
# include "BabeSystemImpl.hpp"
# include "BabeNonCopyable.hpp"

namespace Babe
{

  class BABE_DLLREQ Plugin : public NonCopyable
  {
  public:
    Plugin(std::string systemName, std::string version, SystemImplFactory* factory);
    Plugin(SystemImplFactory* factory);
    void init(std::string const& systemName, std::string const& pluginName, std::string const& version);
    virtual ~Plugin();
    virtual std::string const& getName() const;
    virtual std::string const& getSystemName() const;
    virtual std::string const& getVersion() const;
    virtual bool initialize();
    virtual bool shutdown();

  protected:
    std::string		mSystemName;
    std::string		mPluginName;
    std::string		mVersion;
    SystemImplFactory*	mFactory;
    SystemImpl*		mManagerImpl;
    bool		mIsInit;
  };

} // End of namespace Babe

#endif		// ! __BABE_PLUGIN_HPP__


#ifndef		__BABE_APPLICATIONSETTINGS_HPP__
# define	__BABE_APPLICATIONSETTINGS_HPP__

# include <string>
# include <fstream>
# include <vector>
# include "BabeDef.hpp"
# include "BabeSingleton.hpp"
# include "BabeXMLDocument.hpp"

namespace Babe
{

  class BABE_DLLREQ ApplicationSettings : public Singleton<ApplicationSettings>
  {
  public:
    ApplicationSettings(std::string const& applicationName, std::string const& prefixPath);
    virtual ~ApplicationSettings();
    std::string const& getConfigFileName() const;
    bool getEntries();
    XMLDocument::AttributeMap getSystemAttributes(std::string const& systemName);
    std::string getSystemAttribute(std::string const& systemName, std::string const& attributeName);
    static ApplicationSettings* getSingletonPtr();
    static ApplicationSettings& getSingleton();

  private:
    bool getSystemEntries();
    void getMainTargetRate();

  public:
    struct SystemEntries
    {
      SystemEntries() : initOrdering(-1), runOrdering(-1), targetRate(0.0f) {}
      bool		isPlugin;
      std::string	pluginPath;
      std::string	pluginName;
      std::string	systemName;
      int		initOrdering;
      int		runOrdering;
      float		targetRate;
    };
    typedef std::vector<SystemEntries> SystemEntriesVector;

  private:
    std::string			mConfigFileName;
    std::ifstream		mConfigFile;
    bool			mIsEntries;
    XMLDocument*       		mDocument;

  public:
    SystemEntriesVector		mSystemEntries;
  };

} // End of namespace Babe

#endif		// ! __BABE_APPLICATIONSETTINGS_HPP__

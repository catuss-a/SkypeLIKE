
#include <stdexcept>
#include <iostream>
#include <sstream>
#include "BabeLogManager.hpp"
#include "BabeApplicationSettings.hpp"
#include "BabeLogManager.hpp"
#include "BabeStringUtils.hpp"
#include "BabeApplicationUpdateHandler.hpp"

namespace Babe
{
	ApplicationSettings* ApplicationSettings::getSingletonPtr()
	{
		return msSingleton;
	}

	ApplicationSettings& ApplicationSettings::getSingleton()
	{
        ASSERT_SINGLETON( msSingleton, "ApplicationSettings", "getSingleton()" );  return ( *msSingleton );  
	}

	ApplicationSettings::ApplicationSettings(std::string const& applicationName, std::string const& prefixPath)
    : mConfigFileName(prefixPath + "Config" + applicationName + ".xml"),
      mIsEntries(false)
  {
    LOG("ApplicationSettings created");
    mDocument = new XMLDocument(mConfigFileName);
  }

  ApplicationSettings::~ApplicationSettings()
  {
    LOG("Destroying ApplicationSettings...");
    if (mDocument)
      delete mDocument;
  }

  std::string const& ApplicationSettings::getConfigFileName() const
  {
    return mConfigFileName;
  }

  bool ApplicationSettings::getEntries()
  {
    mIsEntries = getSystemEntries();
    if (!mIsEntries)
      return mIsEntries;
    getMainTargetRate();
    return mIsEntries;
  }

  XMLDocument::AttributeMap ApplicationSettings::getSystemAttributes(std::string const& systemName)
  {
    std::string tag = StringUtils::toLower(StringUtils::cutEnd(systemName, "System"));
    return mDocument->getNodeAttributes(tag);
  }

  std::string ApplicationSettings::getSystemAttribute(std::string const& systemName, std::string const& attributeName)
  {
    std::string attributeValue;
    XMLDocument::AttributeMap map = getSystemAttributes(systemName);
    XMLDocument::AttributeMap::iterator found = map.find(attributeName);
    if (found != map.end())
      attributeValue = found->second;
    return attributeValue;
  }

  bool ApplicationSettings::getSystemEntries()
  {
    XMLDocument::AttributeMapVector atr = mDocument->getNodeListAttributes("systems", "system");
    for (XMLDocument::AttributeMapVector::iterator i = atr.begin(); i != atr.end(); ++i)
      {
	SystemEntries system;
	XMLDocument::AttributeMap map = *i;
	XMLDocument::AttributeMap::iterator found;
	system.isPlugin = false;
	found = map.find("type");
	if (found != map.end())
	  system.systemName.assign(found->second + "System");
	else
	  throw std::runtime_error("A system needs to have an attribute \"type\".");
	found = map.find("plugin_path");
	if (found != map.end())
	  {
	    system.isPlugin = true;
	    system.pluginPath.assign(found->second);
	    found = map.find("plugin_name");
	    if (found != map.end())
	      system.pluginName.assign(found->second);
	    else
	      throw std::runtime_error("A plugin should have an attribute \"plugin_name\"");
	  }
	found = map.find("init_ordering");
	if (found != map.end())
	  {
	    std::istringstream iss(found->second);
	    iss >> system.initOrdering;
	  }
	found = map.find("run_ordering");
	if (found != map.end())
	  {
	    std::istringstream iss(found->second);
	    iss >> system.runOrdering;
	  }
	found = map.find("target_rate");
	if (found != map.end())
	  {
	    std::istringstream iss(found->second);
	    iss >> system.targetRate;
	  }
	mSystemEntries.push_back(system);
      }
    return true;
  }

  void ApplicationSettings::getMainTargetRate()
  {
    XMLDocument::AttributeMap attr = mDocument->getNodeAttributes("systems");;
    XMLDocument::AttributeMap::iterator i = attr.find("target_rate");
    if (i != attr.end())
      ApplicationUpdateHandler::getSingletonPtr()->setTargetRate(StringUtils::toFloat(i->second));
  }

} // End of namespace Babe

//
// BabeLogManager.hpp for  in /home/champi_d//AdvancedCPP/Babel/Babe
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Nov 13 19:41:33 2011 alexandre champion
// Last update Mon Nov 28 17:57:56 2011 alexandre champion
//

#ifndef		__BABE_LOGMANAGER_HPP__
# define	__BABE_LOGMANAGER_HPP__

# include <iostream>
# include <string>
# include <fstream>
# include "BabeDef.hpp"
# include "BabeSingleton.hpp"

namespace Babe
{

  class BABE_DLLREQ LogManager : public Singleton<LogManager>
  {
  public:
    LogManager(std::string const & name);
    virtual ~LogManager();
    void logMessage(std::string const& message);
    void logErrorMessage(std::string const& errorMessage);
    void logCommand(std::string const& command);
    void setIsActive(bool isActive);
	static LogManager* getSingletonPtr();
	static LogManager& getSingleton();

  private:
    bool		mCanOpen;
    std::string		mLogName;
    std::string		mLogErrName;
    std::string		mLogCmdName;
    std::ofstream	mFileLog;
    std::ofstream	mFileErrLog;
    std::ofstream	mFileCmdLog;
    bool		mIsActive;
  };

  #define LOG(X)	LogManager::getSingletonPtr()->logMessage(X)
  #define LOGE(X)	LogManager::getSingletonPtr()->logErrorMessage(X)
  #define LOGCMD(X)	LogManager::getSingletonPtr()->logCommand(X)
  
	template BABE_DLLREQ class Singleton<LogManager>;

} // End of namespace Babe

#endif		// ! __BABE_LOGMANAGER_HPP__

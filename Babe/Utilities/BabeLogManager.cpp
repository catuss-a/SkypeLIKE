//
// BabeLogManager.cpp for  in /home/champi_d//AdvancedCPP/Babel/Babe
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Nov 13 19:41:37 2011 alexandre champion
// Last update Sat Dec  3 13:25:20 2011 alexandre champion
//

#include <iostream>
#include "BabeLogManager.hpp"

namespace Babe
{
	LogManager* LogManager::getSingletonPtr(void)
    {
        return msSingleton;
    }

    LogManager& LogManager::getSingleton(void)
    {  
        ASSERT_SINGLETON( msSingleton, "LogManager", "getSingleton()" );  return ( *msSingleton );  
    }

  LogManager::LogManager(std::string const & name)
    : mCanOpen(true),
      mLogName("LOG_" + name),
      mLogErrName("LOGE_" + name),
      mLogCmdName("LOGCMD_" + name),
      mIsActive(true)
  {
    mFileLog.open(mLogName.c_str());
    if (!mFileLog.is_open())
      mCanOpen = false;
    mFileErrLog.open(mLogErrName.c_str());
    if (!mFileErrLog.is_open())
      mCanOpen = false;
    mFileCmdLog.open(mLogCmdName.c_str());
    if (!mFileCmdLog.is_open())
      mCanOpen = false;
  }
  
  LogManager::~LogManager()
  {
    if (mCanOpen)
      {
	mFileLog.close();
	mFileErrLog.close();
	mFileCmdLog.close();
      }
  }

  void	LogManager::logMessage(std::string const& message)
  {
    if (!mIsActive)
      return ;
    if (mCanOpen)
      mFileLog << message << std::endl;
    else
      std::cout << message << std::endl;
  }

  void	LogManager::logErrorMessage(std::string const& errorMessage)
  {
    if (!mIsActive)
      return ;
    logMessage(errorMessage);
    if (mCanOpen)
      mFileErrLog << errorMessage << std::endl;
    else
      std::cerr << errorMessage << std::endl;
  }

  void	LogManager::logCommand(std::string const& message)
  {
    if (!mIsActive)
      return ;
    if (mCanOpen)
      mFileCmdLog << message << std::endl;
    else
      std::cout << message << std::endl;
  }

  void LogManager::setIsActive(bool isActive)
  {
    mIsActive = isActive;
  }
  
} // End of namespace Babe

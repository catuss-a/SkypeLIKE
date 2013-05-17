//
// NetworkManagerNinaImpl.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
//
// Made by alexandre champion
// Login   <champi_d@epitech.net>
//
// Started on  Mon Nov 28 22:54:28 2011 alexandre champion
// Last update Sun Dec  4 21:12:51 2011 alexandre champion
//

#include "NinaTime.hpp"
#include "NinaError.hpp"
#include "NetworkManagerNinaImpl.hpp"

NetworkManagerNinaImpl::NetworkManagerNinaImpl()
  : mAudio(0),
    mCommand(0),
    mIsconnected(false)
{
}

NetworkManagerNinaImpl::~NetworkManagerNinaImpl()
{
}

bool NetworkManagerNinaImpl::init()
{
  setDefaultConnection();
  connect(mDefaultHost, mDefaultPort, familyFromString(mDefaultFamily));
  Babe::LOG("NetworkManagerNinaImpl initialized");
  return true;
}

void NetworkManagerNinaImpl::shutdown()
{
  if (isConnected()) {
    delete mCommand;
    delete mAudio;
    mIsconnected = false;
    mCommand = 0;
    mAudio = 0;
  }
}

void NetworkManagerNinaImpl::update(float)
{
  int errCode;

  errCode = mReactor.handleEvents(&NINA::Time::timeNull);
  if (errCode < 0)
    Babe::LOGE("[NetworkManagerNinaImpl::update] Error updating : "
	       + NINA::Error::getLastError());
}

bool NetworkManagerNinaImpl::sendMessage(std::string const& message)
{
  if (!mIsconnected)
    return false;
  Babe::LOG("NetworkManagerNinaImpl::sendMessage(\"" + message + "\")");
  return mCommand->sendMessage(message);
}

bool NetworkManagerNinaImpl::sendData(size_t dataSize, void* data)
{
  if (!mIsconnected)
    return false;
  Babe::LOG("NetworkManagerNinaImpl::sendData()");
  return mAudio->sendData(dataSize, data);
}

bool NetworkManagerNinaImpl::isConnected() const
{
	return mIsconnected;	
}

void NetworkManagerNinaImpl::setIsConnected(bool status)
{
  mIsconnected = status;
  if (!status)
    {
      mCommand = 0;
      delete mAudio;
    }
}

bool NetworkManagerNinaImpl::connect(std::string const& hostName, std::string const& port, Babe::NetworkManagerImpl::eConnectionFamily family)
{
  bool	commandSucceeded = false;

  if (isConnected())
    {
      delete mCommand;
      delete mAudio;
      mCommand = 0;
      mAudio = 0;
    }
  try
    {
      mIsconnected = true;
      if (family == Babe::NetworkManagerImpl::IPV6)
	{
	  mCommand = new BabelService(hostName, port, AF_INET6);
	  commandSucceeded = true;
	  mAudio = new AudioService(port, AF_INET6);
	}
      else
	{
	  mCommand = new BabelService(hostName, port);
	  commandSucceeded = true;
	  mAudio = new AudioService(port);
	}
    }
  catch (NINA::Error::SystemError& e)
    {
      Babe::CommandManager::getSingletonPtr()->execute("error Connection failed : " + NINA::Error::getLastError());
      mIsconnected = false;
      delete mCommand;
      if (commandSucceeded)
	delete mAudio;
      return false;
    }
return true;
}

void NetworkManagerNinaImpl::setDefaultConnection()
{
  Babe::ApplicationSettings* settings = Babe::ApplicationSettings::getSingletonPtr();
  mDefaultHost = settings->getSystemAttribute("NetworkSystem", "host");
  if (mDefaultHost.empty())
    mDefaultHost = "127.0.0.1";
  mDefaultPort = settings->getSystemAttribute("NetworkSystem", "port");
  if (mDefaultPort.empty())
    mDefaultPort = "sip";
  mDefaultFamily = settings->getSystemAttribute("NetworkSystem", "family");
  if (mDefaultFamily.empty())
    mDefaultFamily = "IPv4";
}

Babe::NetworkManagerImpl::eConnectionFamily NetworkManagerNinaImpl::familyFromString(std::string const& family)
{
  NetworkManagerImpl::eConnectionFamily efamily;
  if ((family == "ipv6") || (family == "IPV6") || (family == "IPv6"))
    efamily = NetworkManagerImpl::IPV6;
  else
    efamily = NetworkManagerImpl::IPV4;
  return efamily;
}

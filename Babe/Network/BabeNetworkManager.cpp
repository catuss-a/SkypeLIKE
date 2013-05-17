//
// BabeNetworkManager.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Mon Nov 28 18:42:36 2011 alexandre champion
// Last update Sat Dec  3 17:05:33 2011 alexandre champion
//

#include "BabeNetworkManager.hpp"
#include "BabeLogManager.hpp"

namespace Babe
{
  NetworkManager* NetworkManager::getSingletonPtr()
  {
    return msSingleton;
  }

  NetworkManager& NetworkManager::getSingleton()
  {
    ASSERT_SINGLETON( msSingleton, "NetworkManager", "getSingleton()" );  return ( *msSingleton );
  }

  NetworkManager::NetworkManager()
    : System("NetworkSystem")
  {
    mImpl = &mDummyImpl;
    LOG("NetworkManager created");
  }

  NetworkManager::~NetworkManager()
  {
  }

  bool NetworkManager::init()
  {
    return mImpl->init();
  }

  void NetworkManager::shutdown()
  {
    mImpl->shutdown();
  }

  void NetworkManager::update(float dt)
  {
    mImpl->update(dt);
  }
  
  bool NetworkManager::isConnected() const
  {
    return mImpl->isConnected();
  }

  void NetworkManager::setIsConnected(bool status)
  {
    mImpl->setIsConnected(status);
  }

  bool NetworkManager::connect(std::string const& hostName, std::string const& port, NetworkManagerImpl::eConnectionFamily family)
  {
    return mImpl->connect(hostName, port, family);
  }

  bool NetworkManager::sendMessage(std::string const& message)
  {
    return mImpl->sendMessage(message);
  }

  bool NetworkManager::sendData(size_t dataSize, void* data)
  {
    return mImpl->sendData(dataSize, data);
  }

  void NetworkManager::setImpl(SystemImpl* impl)
  {
    if (impl)
      {
	if (!(mImpl = dynamic_cast<NetworkManagerImpl*>(impl)))
	  {
	    LOGE("NetworkManager::setImpl the implementation is not a NetworkManagerImpl*");
	    mImpl = &mDummyImpl;
	  }
      }
  }

  void NetworkManager::unsetImpl()
  {
    mImpl = &mDummyImpl;
  }

} // End of namespace Babe

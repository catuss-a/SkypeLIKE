//
// BabeNetworkManager.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Mon Nov 28 18:42:30 2011 alexandre champion
// Last update Sat Dec  3 17:04:12 2011 alexandre champion
//

#ifndef		__BABE_NETWORKMANAGER_HPP__
# define	__BABE_NETWORKMANAGER_HPP__

# include <string>
# include "BabeDef.hpp"
# include "BabeSingleton.hpp"
# include "BabeSystem.hpp"
# include "BabeNetworkManagerImpl.hpp"

namespace Babe
{

  class BABE_DLLREQ NetworkManager : public Singleton<NetworkManager>, public System
  {
  public:
    NetworkManager();
    virtual ~NetworkManager();
    virtual bool init();
    virtual void shutdown();
    virtual void update(float dt);
    bool isConnected() const;
    void setIsConnected(bool);
    bool connect(std::string const& hostName, std::string const& port, NetworkManagerImpl::eConnectionFamily family = NetworkManagerImpl::IPV4);
    bool sendMessage(std::string const& message);
    bool sendData(size_t dataSize, void* data);
    virtual void setImpl(SystemImpl* impl);
    virtual void unsetImpl();
    static NetworkManager* getSingletonPtr();
    static NetworkManager& getSingleton();

  private:
    NetworkManagerDummyImpl	mDummyImpl;
    NetworkManagerImpl*		mImpl;
  };

} // End of namespace Babe

#endif		// ! __BABE_NETWORKMANAGER_HPP__

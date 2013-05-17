//
// BabeNetworkManagerImpl.hpp for ] in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Mon Nov 28 18:44:00 2011 alexandre champion
// Last update Sat Dec  3 17:08:52 2011 alexandre champion
//

#ifndef		__BABE_NETWORKMANAGERIMPL_HPP__
# define	__BABE_NETWORKMANAGERIMPL_HPP__

# include <string>
# include "BabeDef.hpp"
# include "BabeSystemImpl.hpp"
# include "BabeLogManager.hpp"

namespace Babe
{
  
  class BABE_DLLREQ NetworkManagerImpl : public SystemImpl
  {
  public:
    enum eConnectionFamily
    {
      IPV4,
      IPV6
    };

  public:
    virtual ~NetworkManagerImpl() {}
    virtual bool init() = 0;
    virtual void shutdown() = 0;
    virtual void update(float dt) = 0;    
    virtual bool isConnected() const = 0;
    virtual void setIsConnected(bool) = 0;
    virtual bool connect(std::string const&, std::string const&, NetworkManagerImpl::eConnectionFamily) = 0;
    virtual bool sendMessage(std::string const& message) = 0;
    virtual bool sendData(size_t dataSize, void* data) = 0;
  };

  class BABE_DLLREQ NetworkManagerDummyImpl : public NetworkManagerImpl
  {
  public:
    NetworkManagerDummyImpl() {}
    virtual ~NetworkManagerDummyImpl() {}
    virtual bool init() { LOG("NetworkManagerDummyImpl initialized"); return true; }
    virtual void shutdown() {}
    virtual void update(float) {}
    virtual bool isConnected() const { return true; }
    virtual void setIsConnected(bool) { }
    virtual bool connect(std::string const&, std::string const&, NetworkManagerImpl::eConnectionFamily) { return true; }
    virtual bool sendMessage(std::string const& message) { LOG("NetworkManagerDummyImpl sendMessage(\"" + message + "\")"); return true; }
    virtual bool sendData(size_t, void*) { LOG("NetworkManagerDummyImpl sendData()"); return true; }
  };

} // End of namespace Babe

#endif		// ! __BABE_NETWORKMANAGERIMPL_HPP__

//
// NetworkManagerNinaImpl.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Mon Nov 28 22:54:07 2011 alexandre champion
// Last update Sun Dec  4 16:33:56 2011 alexandre champion
//

#ifndef		__NETWORKMANAGERNINAIMPL_HPP__
# define	__NETWORKMANAGERNINAIMPL_HPP__

# include <Babe.hpp>
# include "AudioService.hpp"
# include "BabelService.hpp"

class BABE_DLLREQ NetworkManagerNinaImpl : public Babe::NetworkManagerImpl
{
 public:
  NetworkManagerNinaImpl();
  virtual ~NetworkManagerNinaImpl();
  virtual bool init();
  virtual void shutdown();
  virtual void update(float dt);
  virtual bool sendMessage(std::string const& message);
  virtual bool sendData(size_t dataSize, void* data);
  virtual bool isConnected() const;
  virtual void setIsConnected(bool);
  virtual bool connect(std::string const& hostName, std::string const& port, Babe::NetworkManagerImpl::eConnectionFamily family);
  
 private:
  void setDefaultConnection();
  Babe::NetworkManagerImpl::eConnectionFamily familyFromString(std::string const& family);
  
 private:
  NINA::Reactor<>	mReactor;
  AudioService*		mAudio;
  BabelService*		mCommand;
  bool		       	mIsconnected;
  std::string		mDefaultHost;
  std::string		mDefaultPort;
  std::string		mDefaultFamily;
};

#endif		// ! __NETWORKMANAGERNINAIMPL_HPP__

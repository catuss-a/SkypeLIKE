#ifndef __AUDIOSERVICE_HPP__
# define __AUDIOSERVICE_HPP__

# include <map>
# include <list>
# include "NinaCppUtils.hpp"
# include "NinaEventHandler.hpp"
# include "NinaSockDatagram.hpp"
# include "NinaInetAddr.hpp"
# include "NinaSockConnector.hpp"
# include "NinaPacket.hpp"
# include "NinaReactor.hpp"

class AudioService : public NINA::EventHandler
{
private:
  typedef std::map<std::string, NINA::InetAddr> UDPFilters;
  typedef std::list<NINA::OutputPacket> PacketList;

public:
  AudioService(std::string const& port, int family = AF_INET);
  ~AudioService();

public:
  static AudioService* get();
  virtual int handleUrgent(NINA::NINAHandle);
  virtual int handleSignal(NINA::NINAHandle);
  virtual int handleTimeout(NINA::NINAHandle);
  virtual int handleWrite(NINA::NINAHandle);
  virtual int handleRead(NINA::NINAHandle);
  virtual int handleClose(NINA::NINAHandle);
  bool sendData(size_t dataSize, void* data);
  virtual NINA::NINAHandle getHandle() const;
  void addUDPFilter(NINA::CDR::String const& login, NINA::CDR::String const& addr);
  void removeUDPFilter();
  void setUDPFilter(NINA::CDR::String const& login);

private:
  std::string			mPort;
  NINA::InetAddr		mLocalAddr;
  NINA::SockDatagram	mSock;
  NINA::SockConnector mConnector;
  NINA::Reactor<>* 	mReactor;
  Babe::AudioManager*	mAudioManager;
  UDPFilters			mFilters;
  NINA::InetAddr*		mRemoteAddr;
  bool				mIgnoreError;
  std::string			mRecord;
  size_t				mCapacity;
  NINA::CDR::ULong	mTimestamp;
  PacketList			mList;
  static AudioService*		mInstance;
};

#endif /* !__AUDIOSERVICE_HPP__ */

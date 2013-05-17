#ifndef __BABELSERVICE_HPP__
# define __BABELSERVICE_HPP__

# include "NinaSockStream.hpp"
# include "NinaEventHandler.hpp"
# include "NinaInetAddr.hpp"
# include "NinaSockConnector.hpp"
# include "NinaPacketFactory.hpp"
# include "NinaReactor.hpp"

# include "PacketManager.hpp"

class PacketCrafter;

class BabelService : public NINA::EventHandler
{
private:
  enum { RECORD_SZ = 512 };

public:
  BabelService(std::string const& hostname, std::string const& port, int family = AF_INET);
  ~BabelService();

public:
  virtual int handleUrgent(NINA::NINAHandle);
  virtual int handleSignal(NINA::NINAHandle);
  virtual int handleTimeout(NINA::NINAHandle);
  virtual int handleWrite(NINA::NINAHandle);
  virtual int handleRead(NINA::NINAHandle);
  virtual int handleClose(NINA::NINAHandle);
  virtual NINA::NINAHandle getHandle() const;
  bool sendMessage(std::string const& message);

private:
  void manageIncomingPackets();

private:
  NINA::InetAddr			mRemoteAddr;
  NINA::SockStream 		mSock;
  NINA::SockConnector		mConnector;
  NINA::PacketFactory<>*	mPacketFactory;
  NINA::Reactor<>*		mReactor;
  std::string				mRecord;
  PacketManager			mPacketManager;
  PacketCrafter*			mPacketCrafter;
  bool					mIgnoreError;
};

#endif /* !__BABELSERVICE_HPP__ */

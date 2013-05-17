#include "NinaError.hpp"

#include "PacketCrafter.hpp"
#include "Protocol.hpp"

BabelService::BabelService(std::string const& hostname, std::string const& port, int family)
	: mRemoteAddr(family),
	mReactor(NINA::Reactor<>::getSingletonPtr()),
	mIgnoreError(false)
{
	std::string sequence;
	try {
		mRemoteAddr.remoteQuery(hostname, port, "tcp");
		if (mSock.open(NINA::Addr::sapAny, family) < 0 || mConnector.connect(mSock, mRemoteAddr) < 0
				|| mReactor->registerHandler(this, NINA::Events::READ) < 0)
			NINA::Error::throwLastError();
	}
	catch (NINA::Error::SystemError& e) {
		throw;
	}
	sequence.push_back(Protocol::SEQUENCE_ESC);
	sequence.push_back(Protocol::SEQUENCE_INS);
	mPacketFactory = new NINA::PacketFactory<>(sequence);
	mPacketCrafter = new PacketCrafter(*this);
	mRecord.reserve(RECORD_SZ);
}

BabelService::~BabelService()
{
	mIgnoreError = true;
	mReactor->removeHandler(this, NINA::Events::ALL);
	delete mPacketFactory;
	delete mPacketCrafter;
}

int
BabelService::handleUrgent(NINA::NINAHandle)
{
  return 0;
}

int
BabelService::handleSignal(NINA::NINAHandle)
{
  return 0;
}

int
BabelService::handleTimeout(NINA::NINAHandle)
{
  return 0;
}

int
BabelService::handleWrite(NINA::NINAHandle)
{
	int						len;
	std::string				packetDump;
	int						errCode = 0;
	PacketCrafter::iterator i = mPacketCrafter->begin();

	while (i != mPacketCrafter->end()) {
		packetDump = i->dump();
		len = mSock.send(packetDump);
		if (len < 0) {
			NINA::Error::printLastError("[BabelService::handleWrite] send : ");
			++i;
		}
		else if (len < static_cast<int> (packetDump.size())) {
			i->assign(packetDump.substr(len));
			++i;
		}
		else
			i = mPacketCrafter->remove(i);
	}
	if (mPacketCrafter->empty())
		errCode = mReactor->removeHandler(this, NINA::Events::WRITE);
		return errCode;
}

int
BabelService::handleRead(NINA::NINAHandle)
{
	int								errCode;

	errCode = mSock.receive(mRecord);
	if (errCode == 0) {
		std::cout << "Server at " << mRemoteAddr.getHostAddr() << " has shutdown" << std::endl;
		delete this;
		Babe::NetworkManager::getSingletonPtr()->setIsConnected(false);
		Babe::CommandManager::getSingletonPtr()->execute("connectionlost");
		errCode = 1;
	}
	else if (errCode > 0) {
		mPacketFactory->pushStream(mRecord);
		mRecord.clear();
		if (!mPacketFactory->empty())
			manageIncomingPackets();
		else
			errCode = 0;
		mRecord.clear();
	}
	return errCode;
}

int
BabelService::handleClose(NINA::NINAHandle)
{
	if (NINA::Error::pendingError() && !mIgnoreError)
		NINA::Error::printLastError("[BabelService::handleClose] handler error : ");
	mIgnoreError = false;
	return 0;
}

NINA::NINAHandle
BabelService::getHandle() const
{
  return mSock.getHandle();
}

bool
BabelService::sendMessage(std::string const& message)
{
  return mPacketCrafter->sendMessage(message);
}


void
BabelService::manageIncomingPackets()
{
	NINA::PacketFactory<>::iterator i  = mPacketFactory->begin();

	while (i != mPacketFactory->end()) {
		mPacketManager.managePacket(*i);
		i = mPacketFactory->remove(i);
	}
	mPacketFactory->clear();
}

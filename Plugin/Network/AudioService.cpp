#include "Babe.hpp"

#include "NinaTime.hpp"
#include "NinaError.hpp"

#include "Protocol.hpp"
#include "AudioService.hpp"

AudioService* AudioService::mInstance = 0;

AudioService::AudioService(std::string const& port, int family)
  : mPort(port),
    mLocalAddr(family),
    mReactor(NINA::Reactor<>::getSingletonPtr()),
    mAudioManager(Babe::AudioManager::getSingletonPtr()),
    mRemoteAddr(0),
    mIgnoreError(false),
	mCapacity(0)
{
   try {
    mLocalAddr.wildcardQuery(mPort, "udp");
    if (mSock.open(mLocalAddr, family) < 0 ||
			mSock.enable(NINA::SAP::NON_BLOCK) < 0 ||
			mReactor->registerHandler(this, NINA::Events::READ) < 0)
      NINA::Error::throwLastError();
  }
  catch (NINA::Error::SystemError& e) {
    throw;
  }
  mInstance = this;
}

AudioService::~AudioService()
{
  mIgnoreError = true;
  mReactor->removeHandler(this, NINA::Events::ALL);
  mInstance = 0;
}

AudioService* AudioService::get()
{
  return mInstance;
}

int
AudioService::handleUrgent(NINA::NINAHandle)
{
  return 0;
}

int
AudioService::handleSignal(NINA::NINAHandle)
{
  return 0;
}

int
AudioService::handleTimeout(NINA::NINAHandle)
{
  return 0;
}

int
AudioService::handleWrite(NINA::NINAHandle)
{
  int	errCode = 0;

  if (mRemoteAddr) {
    for (PacketList::iterator i = mList.begin(); i != mList.end(); i = mList.erase(i)) {
      if (mSock.exactSendToPeer(i->dump(), *mRemoteAddr) < 0)
	NINA::Error::printLastError("[AudioService::handleWrite] exactSendToPeer : ");
    }
    if (mList.empty())
      errCode = mReactor->removeHandler(this, NINA::Events::WRITE);
  }
  return errCode;
}

int
AudioService::handleRead(NINA::NINAHandle)
{
	int					errCode;
	NINA::InetAddr		peerAddr;
	NINA::InputPacket	ip;
	NINA::CDR::UChar	rawData;
	NINA::CDR::ULong	timestamp;
	NINA::CDR::String	frame;
	size_t				frameSize = mAudioManager->getAudioEncFrameSize();

	if (mCapacity == 0 || mRecord.capacity() != mCapacity) {
		mCapacity = sizeof(NINA::CDR::UChar) + sizeof(NINA::CDR::ULong) + frameSize;
		mRecord.reserve(mCapacity);
	}
	do {
		errCode = mSock.exactReceiveFromPeer(mRecord, &peerAddr);
		if (errCode > 0 && mRemoteAddr && peerAddr == *mRemoteAddr) {
			ip.assign(mRecord);
			ip >> rawData >> timestamp;
			ip.get(frame, frameSize);
			if (rawData == Protocol::AUDIO && timestamp >= mTimestamp) {
				mTimestamp = timestamp;
				mAudioManager->playAudioFrame(frame.c_str(), frame.size());
			}
		}
	}
	while (errCode > 0);
	if (errCode < 0 && errno != EAGAIN)
		return errCode;
	return 0;
}

	int
AudioService::handleClose(NINA::NINAHandle)
{
	if (NINA::Error::pendingError() && !mIgnoreError)
		NINA::Error::printLastError("[AudioService::handleClose] handler error : ");
	mIgnoreError = false;
	return 0;
}

	bool
AudioService::sendData(size_t dataSize, void* data)
{
	NINA::OutputPacket	op;
	NINA::Time			time(NINA::Time::timeNull);
	std::stringbuf		sb;
	std::streamsize		frameSize = mAudioManager->getAudioEncFrameSize();
	char*				frame = new char[frameSize];

	if (dataSize >= static_cast<size_t>(frameSize)) {
		frame = new char[frameSize];
		if (mList.empty() && mReactor->registerHandler(this, NINA::Events::WRITE) < 0)
			NINA::Error::printLastError("[AudioService::sendData] registerHandler : ");
		sb.str(std::string(static_cast<char*>(data), dataSize));
		while (sb.sgetn(frame, frameSize) == frameSize) {
			if (time.timestamp() < 0) {
				NINA::Error::printLastError("[AudioService::sendData] timestamp : ");
				continue;
			}
			op << NINA::CDR::UChar(Protocol::AUDIO) << NINA::CDR::ULong(time.getSeconds() * NINA::Time::SEC_IN_USEC + time.getUSeconds()) <<
				NINA::CDR::String(std::string(frame, frameSize));
			mList.push_back(op);
		}
	}
	delete frame;
	return true;
}

	void
AudioService::addUDPFilter(NINA::CDR::String const& login, NINA::CDR::String const& addr)
{
	NINA::InetAddr	filter;

	filter.remoteQuery(addr, mPort, "udp");
	mFilters[login] = filter;
	setUDPFilter(login);
}

	void
AudioService::removeUDPFilter()
{
	if (mConnector.disconnect(mSock) < 0)
		NINA::Error::printLastError("[AudioService::removeUDPFilter] disconnect : ");
	mRemoteAddr = 0;
}

	void
AudioService::setUDPFilter(NINA::CDR::String const& login)
{
	try {
		mRemoteAddr = &mFilters.at(login);
		if (mConnector.connect(mSock, *mRemoteAddr) < 0)
			NINA::Error::printLastError("[AudioService::setUDPFilter] connect : ");
	}
	catch (std::out_of_range) {}
}

NINA::NINAHandle
AudioService::getHandle() const
{
	return mSock.getHandle();
}

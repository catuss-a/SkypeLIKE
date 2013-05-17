#include <string>
#include "NinaError.hpp"

#include "BabelServer.hpp"
#include "PacketCrafter.hpp"
#include "Protocol.hpp"

BabelService::BabelService()
	: mReactor(NINA::Reactor<>::getSingletonPtr()),
	mUser(0),
	mIsConnected(false),
	mIgnoreError(false)
{
	std::string sequence;

	mPacketCrafter = new PacketCrafter(*this);
	sequence.push_back(Protocol::SEQUENCE_ESC);
	sequence.push_back(Protocol::SEQUENCE_INS);
	mPacketFactory = new NINA::PacketFactory<>(sequence);
	mRecord.reserve(RECORD_SZ);
}

BabelService::~BabelService()
{
	mIgnoreError = true;
	mReactor->removeHandler(this, NINA::Events::ALL);
	unloadUserData();
	delete mPacketFactory;
	delete mPacketCrafter;
}

void
BabelService::serverRegistration(std::string const& username)
{
	BabelServer::getSingleton().mClientConnected[username] = this;
}

void
BabelService::serverUnregistration(std::string const& username) const
{
	BabelServer::getSingleton().mClientConnected.erase(username);
}

void
BabelService::loadUserData(std::string const& username)
{
	std::string contacts;
	std::string contact;

	mUser = new Contact;
	mUser->username = username;
	contacts = BabelServer::getSingleton().databaseAccess().getContacts(username);
	std::istringstream iss(contacts);
	while (iss >> contact)
		mUser->contactList[contact] = IN_BASE;
}

void
BabelService::unloadUserData()
{
	if (mUser) {
		mUser->contactList.clear();
		delete mUser;
		mUser = 0;
	}
}

BabelService::Contact*
BabelService::getUser() const
{
	return mUser;
}

void
BabelService::forcePacketGeneration(NINA::OutputPacket& op)
{
	if (mPacketCrafter->empty() && mReactor->registerHandler(this, NINA::Events::WRITE) < 0)
		NINA::Error::printLastError("[BabelService::forcePacketGeneration] registerHandler : ");
	mPacketCrafter->craftPacket(op);
}

bool
BabelService::isConnected() const
{
	return mIsConnected;
}

void
BabelService::connectionStatus(bool status)
{
	mIsConnected = status;
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
		len = getPeer().send(packetDump);
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

	errCode = getPeer().receive(mRecord);
	if (errCode == 0) {
		std::cout << "Client " << getRemoteAddr().getHostAddr() << " disconnected" << std::endl;
		if (isConnected())
			forceDisconnect();
		delete this;
		errCode = 1;
	}
	else if (errCode > 0) {
		mPacketFactory->pushStream(mRecord);
		if (!mPacketFactory->empty()) {
			generateReplies();
			errCode = mReactor->registerHandler(this, NINA::Events::WRITE);
		}
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

int
BabelService::init()
{
	std::cout << "Client joined : " << getRemoteAddr().getHostAddr() << std::endl;
	return mReactor->registerHandler(this, NINA::Events::READ);
}

void
BabelService::generateReplies()
{
	NINA::PacketFactory<>::iterator i  = mPacketFactory->begin();

	while (i != mPacketFactory->end()) {
		mPacketCrafter->craftReply(*i);
		i = mPacketFactory->remove(i);
	}
}

void
BabelService::forceDisconnect()
{
	// Use loopback processing to craft required packets
	NINA::OutputPacket op;

	op << NINA::CDR::UChar(Protocol::NOTIFY);
	op << NINA::CDR::UChar(Protocol::DISCONNECTED);
	NINA::InputPacket ip(op.dump());
	mPacketCrafter->craftReply(ip);
}

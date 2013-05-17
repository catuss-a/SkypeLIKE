#include "NinaError.hpp"

#include "BabelServer.hpp"

BabelServer::BabelServer(std::string const& port, int family)
	: mAcceptor(&mReactor),
	mLocalAddr(family),
	mDB("db.xml"),
	mIsRunning(false)
{
	try {
		mLocalAddr.wildcardQuery(port, "tcp");
	}
	catch (NINA::Error::SystemError& e) {
		throw;
	}
	if (mAcceptor.open(mLocalAddr, true, PF_UNSPEC, NINA::SockAcceptor::ANY_PROTO, true) < 0)
		NINA::Error::throwLastError();
}

BabelServer::~BabelServer()
{
}

void
BabelServer::run()
{
	int	errCode;

	mIsRunning = true;
	while (mIsRunning) {
		try {
			errCode = mReactor.handleEvents(0);
			if (errCode < 0)
				NINA::Error::printLastError("[BabelServer::run] handleEvents : ");
		}
		catch (NINA::Error::SystemError const& e) {
			std::cerr << e.what() << std::endl;
			// May be suspend()
		}
	}
}

void
BabelServer::suspend()
{
	if (mAcceptor.suspend() < 0)
		NINA::Error::printLastError("[BabelServer::suspend] suspend : ");
}

void
BabelServer::resume()
{
	if (mAcceptor.resume() < 0)
		NINA::Error::printLastError("[BabelServer::resume] resume : ");
}

void
BabelServer::stop()
{
	mIsRunning = false;
}

BabelServer::Services const&
BabelServer::getClients() const
{
	return mClientConnected;
}

void
BabelServer::caching(std::string const& username, NINA::OutputPacket& op)
{
	mCache[username].push_back(op);
}

BabelServer::PendingPackets*
BabelServer::cacheAccess(std::string const& username)
{
	try {
		return &mCache.at(username);
	}
	catch (std::out_of_range) {
		return 0;
	}
}

DB&
BabelServer::databaseAccess()
{
	return mDB;
}

#ifndef __BABELSERVER_HPP__
# define __BABELSERVER_HPP__

# include <map>
# include "NinaInetAddr.hpp"
# include "NinaReactor.hpp"
# include "NinaAcceptor.hpp"

# include "BabelService.hpp"
# include "DB.hpp"

class BabelServer : public NINA::Singleton<BabelServer>
{
	friend class BabelService;

	public:
		typedef std::map<std::string, BabelService*> Services;
		typedef std::vector<NINA::OutputPacket> PendingPackets;
	private:
		typedef std::map<std::string, PendingPackets> PendingAddRequests;

	public:
		BabelServer(std::string const& port, int family = AF_INET);
		~BabelServer();

	public:
		void run();
		void suspend();
		void resume();
		void stop();
	public:
		Services const& getClients() const;
		void caching(std::string const& username, NINA::OutputPacket& op);
		PendingPackets* cacheAccess(std::string const& username);
		DB&	databaseAccess();

	private:
		NINA::Reactor<>					mReactor;
		NINA::Acceptor<BabelService>	mAcceptor;
		NINA::InetAddr					mLocalAddr;
		DB								mDB;
		bool							mIsRunning;
		Services						mClientConnected;
		PendingAddRequests				mCache;
};

#endif /* !__BABELSERVER_HPP__ */

#ifndef __BABELSERVICE_HPP__
# define __BABELSERVICE_HPP__

# include "NinaServiceHandler.hpp"
# include "NinaReactor.hpp"
# include "NinaPacketFactory.hpp"

class PacketCrafter;

class BabelService : public NINA::ServiceHandler<>
{
	public:
		typedef std::map<std::string, uint8_t> ContactList;
		struct Contact {
			std::string username;
			ContactList	contactList;
		};
		enum ContactInfo {
			IN_BASE = 0,
			NEW = 1,
			DELETED = 2
		};
	private:
		enum { RECORD_SZ = 512 };

	public:
		BabelService();
		~BabelService();

	public:
		void serverRegistration(std::string const& username);
		void serverUnregistration(std::string const& username) const;
		void loadUserData(std::string const& username);
		void unloadUserData();
		Contact* getUser() const;
		void forcePacketGeneration(NINA::OutputPacket& op);
		bool isConnected() const;
		void connectionStatus(bool status);
	public:
		int handleWrite(NINA::NINAHandle);
		int handleRead(NINA::NINAHandle);
		int handleClose(NINA::NINAHandle);
		int init();
	private:
		void generateReplies();
		void forceDisconnect();

	private:
		NINA::Reactor<>*		mReactor;
		NINA::PacketFactory<>*	mPacketFactory;
		PacketCrafter*			mPacketCrafter;
		std::string				mRecord;
		Contact*				mUser;
		bool					mIsConnected;
		bool					mIgnoreError;
};

#endif /* !__BABELSERVICE_HPP__ */

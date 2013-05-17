#ifndef __PACKETMANAGER_HPP__
# define __PACKETMANAGER_HPP__

# include "NinaPacket.hpp"
# include "Babe.hpp"

class PacketManager
{
	private:
		typedef void (PacketManager::*Manager)(NINA::InputPacket&);
		typedef std::map<NINA::CDR::UChar, Manager>	AssocTable;

	public:
		PacketManager();
		~PacketManager();

	public:
		void managePacket(NINA::InputPacket& ip);
	private:
		void userConnectionSucceeded(NINA::InputPacket& ip);
		void generalError(NINA::InputPacket& ip);
		void userStatus(NINA::InputPacket& ip);
		void contactRequest(NINA::InputPacket& ip);
		void callManagement(NINA::InputPacket& ip);
		void errorManagement(NINA::InputPacket& ip);
		void receiveText(NINA::InputPacket& ip);

	private:
		Babe::CommandManager*	mCommandManager;
		AssocTable      		mTable;
};

#endif /* !__PACKETMANAGER_HPP__ */

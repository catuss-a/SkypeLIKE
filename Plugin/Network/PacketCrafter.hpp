#ifndef __PACKETCRAFTER_HPP__
# define __PACKETCRAFTER_HPP__

# include <list>
# include <map>
# include <Babe.hpp>
# include "NinaPacket.hpp"
# include "NinaCppUtils.hpp"

# include "BabelService.hpp"

class PacketCrafter : public NINA::NonCopyable
{
	private:
		typedef std::list<NINA::OutputPacket> PacketList;
		typedef void (PacketCrafter::*Crafter)(Babe::CommandParser::ArgVector const& args);
		typedef std::map<std::string, Crafter> CrafterMap;
	public:
		typedef PacketList::iterator iterator;

	public:
		PacketCrafter(BabelService& bs);
		~PacketCrafter();

	public:
		iterator begin();
		iterator end();
		iterator remove(iterator pos);
		bool empty() const;
		bool sendMessage(std::string const& message);

	private:
		void craftUserConnect(Babe::CommandParser::ArgVector const& args);
		void craftUpdateUserStatus(Babe::CommandParser::ArgVector const& args);
		void craftAddContact(Babe::CommandParser::ArgVector const& args);
		void craftAcceptContactRequest(Babe::CommandParser::ArgVector const& args);
		void craftRejectContactRequest(Babe::CommandParser::ArgVector const& args);
		void craftDeleteContact(Babe::CommandParser::ArgVector const& args);
		void craftRequestCall(Babe::CommandParser::ArgVector const& args);
		void craftAcceptCall(Babe::CommandParser::ArgVector const& args);
		void craftRejectCall(Babe::CommandParser::ArgVector const& args);
		void craftHangUpCall(Babe::CommandParser::ArgVector const& args);
		void craftSuspendCall(Babe::CommandParser::ArgVector const& args);
		void craftResumeCall(Babe::CommandParser::ArgVector const& args);
		void craftSendText(Babe::CommandParser::ArgVector const& args);
		
		void craftPacket(NINA::OutputPacket& op);

	private:
		PacketList				mList;
		CrafterMap				mCrafters;
		BabelService&			mService;
		Babe::CommandParser*	mCommandParser;
};

#endif /* !__PACKETCRAFTER_HPP__ */

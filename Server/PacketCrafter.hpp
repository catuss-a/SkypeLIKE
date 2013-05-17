#ifndef __PACKETCRAFTER_HPP__
# define __PACKETCRAFTER_HPP__

# include <list>
# include <map>
# include "NinaPacket.hpp"
# include "NinaCppUtils.hpp"
# include "BabelService.hpp"

class PacketCrafter : public NINA::NonCopyable
{
	private:
		typedef void (PacketCrafter::*Crafter)(NINA::InputPacket&);
		typedef std::list<NINA::OutputPacket> 		PacketList;
		typedef std::map<NINA::CDR::UChar, Crafter>	AssocTable;
	public:
		typedef PacketList::iterator				iterator;

	public:
		PacketCrafter(BabelService& bs);
		~PacketCrafter();

	public:
		void craftPacket(NINA::OutputPacket& op);
		void craftReply(NINA::InputPacket& ip);
		iterator begin();
		iterator end();
		iterator remove(iterator pos);
		bool empty() const;
	private:
		void connectionReply(NINA::InputPacket& ip);
		void notifyReply(NINA::InputPacket& ip);
		void contactReply(NINA::InputPacket& ip);
		void callReply(NINA::InputPacket& ip);
		void textReply(NINA::InputPacket& ip);
		BabelService* getServiceByUser(std::string const& username) const;
		bool isConnected(std::string const& username) const;
		bool inContacts(BabelService::Contact const* user, std::string const& username) const;
		void craftPendingPackets(std::string const& username);
		void syncContacts(BabelService::Contact const* user);
		void craftNotifs(NINA::CDR::UChar type) const;
		void loadContacts();

	private:
		PacketList		mList;
		AssocTable		mTable;
		BabelService&	mService;
};

#endif /* !__PACKETCRAFTER_HPP__ */

#include <stdexcept>
#include "NinaDef.hpp"

#if defined (NINA_WIN32)
# pragma warning (disable : 4251)
#endif

#include "BabelServer.hpp"
#include "PacketCrafter.hpp"
#include "Protocol.hpp"

PacketCrafter::PacketCrafter(BabelService& bs)
	: mService(bs)
{
	mTable[Protocol::CONNECTION] = &PacketCrafter::connectionReply;
	mTable[Protocol::NOTIFY] = &PacketCrafter::notifyReply;
	mTable[Protocol::CONTACT] = &PacketCrafter::contactReply;
	mTable[Protocol::CALL] = &PacketCrafter::callReply;
	mTable[Protocol::TEXT] = &PacketCrafter::textReply;
}

PacketCrafter::~PacketCrafter()
{
}

void
PacketCrafter::craftPacket(NINA::OutputPacket& op)
{
	mList.push_back(op);
}

void
PacketCrafter::craftReply(NINA::InputPacket& ip)
{
	NINA::CDR::UChar	type;
	Crafter				crafter;

	ip >> type;
	try {
		crafter = mTable.at(type);
		(this->*crafter)(ip);
	}
	catch (std::out_of_range) {}
}

PacketCrafter::iterator
PacketCrafter::begin()
{
	return mList.begin();
}

PacketCrafter::iterator
PacketCrafter::end()
{
	return mList.end();
}

PacketCrafter::iterator
PacketCrafter::remove(iterator pos)
{
	return mList.erase(pos);
}

bool
PacketCrafter::empty() const
{
	return mList.empty();
}

void
PacketCrafter::connectionReply(NINA::InputPacket& ip)
{
	NINA::OutputPacket						op;
	NINA::CDR::String						username, password;

	ip >> username >> password;
	bool matchDB = BabelServer::getSingleton().databaseAccess().isMatching(username, password);
	if (matchDB && !isConnected(username)) {
		mService.serverRegistration(username);
		mService.loadUserData(username);
		mService.connectionStatus(true);
		op << NINA::CDR::UChar(Protocol::ESTABLISHED) << NINA::CDR::UShort(Protocol::PROTO_FOOTER);
		craftPacket(op);
		craftNotifs(Protocol::CONNECTED);
		loadContacts();
		craftPendingPackets(username);
	}
	else {
		op << NINA::CDR::UChar(Protocol::ERR) << NINA::CDR::UChar(Protocol::CONNECTING) <<
		(matchDB ? NINA::CDR::String("User already connected") : NINA::CDR::String("Login or password wrong")) <<
	   	NINA::CDR::UShort(Protocol::PROTO_FOOTER);
		craftPacket(op);
	}
}

void
PacketCrafter::notifyReply(NINA::InputPacket& ip)
{
	BabelService::Contact const*    user = mService.getUser();
	NINA::CDR::UChar				notif;

	ip >> notif;
	craftNotifs(notif);		
	if (notif == Protocol::DISCONNECTED) {
		if (user) {
			mService.serverUnregistration(user->username);
			syncContacts(user);
		}
		mService.unloadUserData();
		mService.connectionStatus(false);
	}
}

void
PacketCrafter::contactReply(NINA::InputPacket& ip)
{
	BabelService::Contact*    			user = mService.getUser();
	BabelService*                  		service;
	BabelService::ContactList::iterator		contactFound;
	NINA::CDR::UChar			       	contact;
	NINA::CDR::String		       		login;
	NINA::OutputPacket	       			op;

	ip >> contact >> login;
	if (user)
	{
		contactFound = user->contactList.find(login);
		if (contact == Protocol::REMOVE && contactFound != user->contactList.end())
			contactFound->second = BabelService::DELETED;
		else if (contact == Protocol::ADD || contact == Protocol::ACCEPT)
		{
			if (BabelServer::getSingleton().databaseAccess().exists(login))
			{
				if (!inContacts(user, login))
					user->contactList[login] = BabelService::NEW;
				if (contact == Protocol::ADD)
				{
					op << NINA::CDR::UChar(Protocol::CONTACT) << NINA::CDR::UChar(Protocol::ADD) << NINA::CDR::String(user->username) << NINA::CDR::UShort(Protocol::PROTO_FOOTER);
					if ((service = getServiceByUser(login)))
						service->forcePacketGeneration(op);
					else
						BabelServer::getSingleton().caching(login, op);
				}
			}
			else
			{
				op << NINA::CDR::UChar(Protocol::ERR) << NINA::CDR::UChar(Protocol::CONTACTNOEXIST) <<
					NINA::CDR::String("Contact does not exist : " + login) << NINA::CDR::UShort(Protocol::PROTO_FOOTER);
				craftPacket(op);
			}
		}
	}
}

	void
PacketCrafter::callReply(NINA::InputPacket& ip)
{
	BabelService::Contact const*    			user = mService.getUser();
	BabelService*								service;
	NINA::CDR::UChar							call;
	NINA::CDR::String							login;
	NINA::OutputPacket							op;

	ip >> call >> login;
	service = getServiceByUser(login);
	if (user && service)
	{
		op << NINA::CDR::UChar(Protocol::CALL);
		BabelService::ContactList::const_iterator i = user->contactList.find(login);
		if (i != user->contactList.end() && i->second != BabelService::DELETED)
		{
			op << NINA::CDR::UChar(call) << NINA::CDR::String(user->username);
			if (call == Protocol::REQUEST || call == Protocol::ACCEPTED)
				op << NINA::CDR::Char('\0') << NINA::CDR::String(mService.getRemoteAddr().getHostAddr());
			op << NINA::CDR::UShort(Protocol::PROTO_FOOTER);
			service->forcePacketGeneration(op);
		}
	}
}

	void
PacketCrafter::textReply(NINA::InputPacket& ip)
{
	BabelService::Contact*          user = mService.getUser();
	BabelService*					service;
	NINA::CDR::String				login, text;
	NINA::OutputPacket				op;

	ip >> login >> text;
	if (user && (service = getServiceByUser(login))) {
		op << NINA::CDR::UChar(Protocol::TEXT) << NINA::CDR::String(user->username);
		op << NINA::CDR::Char('\0') << NINA::CDR::String(text.substr(0, 512)) << NINA::CDR::UShort(Protocol::PROTO_FOOTER);
		service->forcePacketGeneration(op);
	}
}

BabelService*
PacketCrafter::getServiceByUser(std::string const& username) const
{
	BabelServer::Services const&  	clients = BabelServer::getSingleton().getClients();
	BabelService*					service;

	try {
		service = clients.at(username);
	}
	catch (std::out_of_range) {
		return 0;
	}
	return service;
}

bool
PacketCrafter::isConnected(std::string const& username) const
{
	BabelServer::Services const&  clients = BabelServer::getSingleton().getClients();

	return (clients.find(username) != clients.end());
}

bool
PacketCrafter::inContacts(BabelService::Contact const* user, std::string const& username) const
{
	return (user->contactList.find(username) != user->contactList.end());
}

	void
PacketCrafter::craftPendingPackets(std::string const& username)
{
	BabelServer::PendingPackets*			serverCache;

	serverCache = BabelServer::getSingleton().cacheAccess(username);
	if (!serverCache)
		return;
	BabelServer::PendingPackets::iterator i = serverCache->begin();
	while (i != serverCache->end()) {
		craftPacket(*i);
		i = serverCache->erase(i);
	}
}

	void
PacketCrafter::syncContacts(BabelService::Contact const* user)
{
	std::ostringstream 	oss;
	bool				sep = false;

	for (BabelService::ContactList::const_iterator i = user->contactList.begin();
			i != user->contactList.end(); ++i) {
		if (i->second != BabelService::DELETED) {
			if (sep)
				oss << " ";
			else
				sep = true;
			oss << i->first;
		}
	}
	BabelServer::getSingleton().databaseAccess().setContacts(user->username, oss.str());
}

void
PacketCrafter::craftNotifs(NINA::CDR::UChar type) const
{
	NINA::OutputPacket				op;
	BabelService*					service;
	BabelService::Contact const*	user = mService.getUser();

	if (user)
	{
		for (BabelService::ContactList::const_iterator i = user->contactList.begin(); i != user->contactList.end(); ++i)
		{
			if (i->second != BabelService::DELETED && (service = getServiceByUser(i->first)))
			{
				op << NINA::CDR::UChar(Protocol::NOTIFY) << type <<
					NINA::CDR::String(user->username) << NINA::CDR::UShort(Protocol::PROTO_FOOTER);
				service->forcePacketGeneration(op);
				op.clear();
			}
		}
	}
}

	void
PacketCrafter::loadContacts()
{
	NINA::OutputPacket              op;
	BabelService::Contact const*	user = mService.getUser();

	if (user) {
		for (BabelService::ContactList::const_iterator i = user->contactList.begin();
				i != user->contactList.end(); ++i) {
			op << NINA::CDR::UChar(Protocol::NOTIFY);
			if (isConnected(i->first))
				op << NINA::CDR::UChar(Protocol::CONNECTED);
			else
				op << NINA::CDR::UChar(Protocol::DISCONNECTED);
			op << NINA::CDR::String(i->first) << NINA::CDR::UShort(Protocol::PROTO_FOOTER);	
			craftPacket(op);
			op.clear();
		}	
	}
}

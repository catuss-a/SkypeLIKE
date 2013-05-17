#include <stdexcept>

#include "PacketManager.hpp"
#include "Protocol.hpp"
#include "AudioService.hpp"

PacketManager::PacketManager()
  : mCommandManager(Babe::CommandManager::getSingletonPtr())
{
	mTable[Protocol::ESTABLISHED] = &PacketManager::userConnectionSucceeded;
	mTable[Protocol::ERR] = &PacketManager::generalError;
	mTable[Protocol::NOTIFY] = &PacketManager::userStatus;
	mTable[Protocol::CONTACT] = &PacketManager::contactRequest;
	mTable[Protocol::CALL] = &PacketManager::callManagement;
	mTable[Protocol::ERR] = &PacketManager::errorManagement;
	mTable[Protocol::TEXT] = &PacketManager::receiveText;
}

PacketManager::~PacketManager()
{
}

void
PacketManager::managePacket(NINA::InputPacket& ip)
{
	NINA::CDR::UChar	type;
	Manager				manager;

	ip >> type;
	try {
		manager = mTable.at(type);
		(this->*manager)(ip);
	}
	catch (std::out_of_range) {}
}

void
PacketManager::userConnectionSucceeded(NINA::InputPacket&)
{
	mCommandManager->execute("userconnectionsucceeded");
}


void
PacketManager::generalError(NINA::InputPacket& ip)
{
  NINA::CDR::String	errorMsg;
  NINA::CDR::UChar	error;

  ip >> error >> errorMsg;
  if (error == Protocol::CONNECTING)
    mCommandManager->execute("userconnectionfailed " + errorMsg);
  else if (error == Protocol::CONTACTNOEXIST)
    mCommandManager->execute("error " + errorMsg);
}

void
PacketManager::userStatus(NINA::InputPacket& ip)
{
	NINA::CDR::UChar    status;
	NINA::CDR::String	login;
	std::string			statusStr;

	ip >> status >> login;
	switch (status) {
		case Protocol::CONNECTED :
			statusStr = "connected";
			break;
		case Protocol::DISCONNECTED :
			statusStr = "disconnected";
			break;
		case Protocol::BUSY :
			statusStr = "busy";
			break;
		case Protocol::ABSENT :
			statusStr = "idle";
			break;
	}
	mCommandManager->execute("userstatus " + login + " " + statusStr);
}

void
PacketManager::contactRequest(NINA::InputPacket& ip)
{
	NINA::CDR::UChar 	contact;
	NINA::CDR::String   login;

	ip >> contact >> login;
	if (contact == Protocol::ADD)
		mCommandManager->execute("contactrequest " + login);	
}

void
PacketManager::callManagement(NINA::InputPacket& ip)
{
	NINA::CDR::UChar call;
	NINA::CDR::String   login;
	NINA::CDR::String   addr;

	ip >> call >> login;
	if (call == Protocol::REQUEST)
	{
		mCommandManager->execute("callrequest " + login);
		ip >> addr;
		if (AudioService::get())
			AudioService::get()->addUDPFilter(login, addr);
		else
			Babe::LOGE("No current AudioService");
	}
	else if (call == Protocol::ACCEPTED)
	{
		mCommandManager->execute("callaccepted " + login);
		ip >> addr;
		if (AudioService::get())
			AudioService::get()->addUDPFilter(login, addr);
		else
			Babe::LOGE("No current AudioService");
	}
	else if (call == Protocol::REJECTED)
		mCommandManager->execute("callrejected " + login);
	else if (call == Protocol::HANGUP)
	{
		mCommandManager->execute("callhungup " + login);
		if (AudioService::get())
			AudioService::get()->removeUDPFilter();
		else
			Babe::LOGE("No current AudioService");
	}
	else if (call == Protocol::SUSPEND)
	{
		mCommandManager->execute("callsuspended " + login);
		if (AudioService::get())
			AudioService::get()->removeUDPFilter();
		else
			Babe::LOGE("No current AudioService");
	}
	else if (call == Protocol::RESUME)
	{
		mCommandManager->execute("callresumed " + login);
		if (AudioService::get())
			AudioService::get()->setUDPFilter(login);
		else
			Babe::LOGE("No current AudioService");
	}
}

	void
PacketManager::errorManagement(NINA::InputPacket& ip)
{
	NINA::CDR::UChar error;
	NINA::CDR::String errorMessage;

	ip >> error >> errorMessage;
	if (error == Protocol::CONNECTING)
	  mCommandManager->execute("error " + errorMessage);
	else if (error == Protocol::CONTACTNOEXIST)
	  mCommandManager->execute("unknowncontact " + errorMessage);
}

	void
PacketManager::receiveText(NINA::InputPacket& ip)
{
	NINA::CDR::String	login, text;

	ip >> login >> text;
	mCommandManager->execute("receivetext " + login + " " + text);
}

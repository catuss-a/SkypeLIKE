#include <stdexcept>
#include "NinaDef.hpp"

#if defined (NINA_WIN32)
# pragma warning (disable : 4251)
#endif

#include "NinaError.hpp"

#include "BabelServer.hpp"
#include "PacketCrafter.hpp"
#include "Protocol.hpp"
#include "AudioService.hpp"

PacketCrafter::PacketCrafter(BabelService& bs)
	: mService(bs),
	mCommandParser(new Babe::CommandParser)
{
  mCrafters["userconnect"] = &PacketCrafter::craftUserConnect;
  mCrafters["updateuserstatus"] = &PacketCrafter::craftUpdateUserStatus;
  mCrafters["addcontact"] = &PacketCrafter::craftAddContact;
  mCrafters["acceptcontactrequest"] = &PacketCrafter::craftAcceptContactRequest;
  mCrafters["rejectcontactrequest"] = &PacketCrafter::craftRejectContactRequest;
  mCrafters["deletecontact"] = &PacketCrafter::craftDeleteContact;
  mCrafters["requestcall"] = &PacketCrafter::craftRequestCall;
  mCrafters["acceptcall"] = &PacketCrafter::craftAcceptCall;
  mCrafters["rejectcall"] = &PacketCrafter::craftRejectCall;
  mCrafters["hangupcall"] = &PacketCrafter::craftHangUpCall;
  mCrafters["suspendcall"] = &PacketCrafter::craftSuspendCall;
  mCrafters["resumecall"] = &PacketCrafter::craftResumeCall;
  mCrafters["sendtext"] = &PacketCrafter::craftSendText;
}

PacketCrafter::~PacketCrafter()
{
}

void
PacketCrafter::craftPacket(NINA::OutputPacket& op)
{
	if (empty() && NINA::Reactor<>::getSingleton().registerHandler(&mService, NINA::Events::WRITE) < 0)
		NINA::Error::printLastError("[PacketCrafter::craftPacket] registerHandler : ");
	mList.push_back(op);
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

bool
PacketCrafter::sendMessage(std::string const& message)
{
  Babe::CommandParser::ParsedCommand pc = mCommandParser->parseCommand(message);
  if (mCrafters.find(pc.name) != mCrafters.end())
    (this->*mCrafters[pc.name])(pc.args);
  return true;
}

void
PacketCrafter::craftUserConnect(Babe::CommandParser::ArgVector const& args)
{
	NINA::OutputPacket	op;

	if (args.size() == 2) {
		op << NINA::CDR::UChar(Protocol::CONNECTION) << NINA::CDR::String(args[0]) <<
		NINA::CDR::Char('\0') << NINA::CDR::String(args[1]) << NINA::CDR::UShort(Protocol::PROTO_FOOTER);
		craftPacket(op);
	}
}

void
PacketCrafter::craftUpdateUserStatus(Babe::CommandParser::ArgVector const& args)
{
  NINA::OutputPacket	op;
  NINA::CDR::UChar	status = Protocol::DISCONNECTED;

  if (args.size() == 1) {
    op << NINA::CDR::UChar(Protocol::NOTIFY);
    if (args[0] == "connected")
      status = Protocol::CONNECTED;
    else if (args[0] == "disconnected")
      status = Protocol::DISCONNECTED;
    else if (args[0] == "busy")
      status = Protocol::BUSY;
    else if (args[0] == "idle")
      status = Protocol::ABSENT;
    op << status << NINA::CDR::UShort(Protocol::PROTO_FOOTER);
    craftPacket(op);
  }
}

void
PacketCrafter::craftAddContact(Babe::CommandParser::ArgVector const& args)
{
	NINA::OutputPacket  op;

	if (args.size() == 1) {
		op << NINA::CDR::UChar(Protocol::CONTACT) << NINA::CDR::UChar(Protocol::ADD)
			<< NINA::CDR::String(args[0]) << NINA::CDR::UShort(Protocol::PROTO_FOOTER);
		craftPacket(op);
	}
}

void
PacketCrafter::craftAcceptContactRequest(Babe::CommandParser::ArgVector const& args)
{
	NINA::OutputPacket  op;

	if (args.size() == 1) {
		op << NINA::CDR::UChar(Protocol::CONTACT) << NINA::CDR::UChar(Protocol::ACCEPT)
			<< NINA::CDR::String(args[0]) << NINA::CDR::UShort(Protocol::PROTO_FOOTER);
		craftPacket(op);
	}
}

void
PacketCrafter::craftRejectContactRequest(Babe::CommandParser::ArgVector const& args)
{
	NINA::OutputPacket  op;

	if (args.size() == 1) {
		op << NINA::CDR::UChar(Protocol::CONTACT) << NINA::CDR::UChar(Protocol::REJECT)
			<< NINA::CDR::String(args[0]) << NINA::CDR::UShort(Protocol::PROTO_FOOTER);
		craftPacket(op);
	}
}

void
PacketCrafter::craftDeleteContact(Babe::CommandParser::ArgVector const& args)
{
	NINA::OutputPacket  op;

	if (args.size() == 1) {
		op << NINA::CDR::UChar(Protocol::CONTACT) << NINA::CDR::UChar(Protocol::REMOVE)
			<< NINA::CDR::String(args[0]) << NINA::CDR::UShort(Protocol::PROTO_FOOTER);
		craftPacket(op);
	}
}

void PacketCrafter::craftRequestCall(Babe::CommandParser::ArgVector const& args)
{
  NINA::OutputPacket  op;

  if (args.size() == 1) {
    op << NINA::CDR::UChar(Protocol::CALL) << NINA::CDR::UChar(Protocol::REQUEST)
       << NINA::CDR::String(args[0]) << NINA::CDR::UShort(Protocol::PROTO_FOOTER);
    craftPacket(op);
  }
}

void PacketCrafter::craftAcceptCall(Babe::CommandParser::ArgVector const& args)
{
  NINA::OutputPacket  op;

  if (args.size() == 1) {
    op << NINA::CDR::UChar(Protocol::CALL) << NINA::CDR::UChar(Protocol::ACCEPTED)
       << NINA::CDR::String(args[0]) << NINA::CDR::UShort(Protocol::PROTO_FOOTER);
    craftPacket(op);
  }
}

void PacketCrafter::craftRejectCall(Babe::CommandParser::ArgVector const& args)
{
  NINA::OutputPacket  op;

  if (args.size() == 1) {
    op << NINA::CDR::UChar(Protocol::CALL) << NINA::CDR::UChar(Protocol::REJECTED)
       << NINA::CDR::String(args[0]) << NINA::CDR::UShort(Protocol::PROTO_FOOTER);
    craftPacket(op);
    if (AudioService::get())
      AudioService::get()->removeUDPFilter();
    else
      Babe::LOGE("No current AudioService");
  }
}

void PacketCrafter::craftHangUpCall(Babe::CommandParser::ArgVector const& args)
{
  NINA::OutputPacket  op;

  if (args.size() == 1) {
    op << NINA::CDR::UChar(Protocol::CALL) << NINA::CDR::UChar(Protocol::HANGUP)
       << NINA::CDR::String(args[0]) << NINA::CDR::UShort(Protocol::PROTO_FOOTER);
    craftPacket(op);
    if (AudioService::get())
      AudioService::get()->removeUDPFilter();
    else
      Babe::LOGE("No current AudioService");
  }
}

void PacketCrafter::craftSuspendCall(Babe::CommandParser::ArgVector const& args)
{
  NINA::OutputPacket  op;

  if (args.size() == 1) {
    op << NINA::CDR::UChar(Protocol::CALL) << NINA::CDR::UChar(Protocol::SUSPEND)
       << NINA::CDR::String(args[0]) << NINA::CDR::UShort(Protocol::PROTO_FOOTER);
    craftPacket(op);
    if (AudioService::get())
      AudioService::get()->removeUDPFilter();
    else
      Babe::LOGE("No current AudioService");
  }
}

void PacketCrafter::craftResumeCall(Babe::CommandParser::ArgVector const& args)
{
  NINA::OutputPacket  op;

  if (args.size() == 1) {
    op << NINA::CDR::UChar(Protocol::CALL) << NINA::CDR::UChar(Protocol::RESUME)
       << NINA::CDR::String(args[0]) << NINA::CDR::UShort(Protocol::PROTO_FOOTER);
    craftPacket(op);
    if (AudioService::get())
      AudioService::get()->setUDPFilter(args[0]);
    else
      Babe::LOGE("No current AudioService");
  }
}

void PacketCrafter::craftSendText(Babe::CommandParser::ArgVector const& args)
{
  NINA::OutputPacket  op;

  if (args.size() >= 2) {
    Babe::CommandParser::ArgVector argsCopy = args;
    std::string login = argsCopy.front();
    argsCopy.pop_front();
    std::string message;
    for (Babe::CommandParser::ArgVector::iterator i = argsCopy.begin(); i != argsCopy.end(); ++i)
      message += (*i) + " ";
    op << NINA::CDR::UChar(Protocol::TEXT) << NINA::CDR::String(login) <<
      NINA::CDR::Char('\0') << NINA::CDR::String(message) << NINA::CDR::UShort(Protocol::PROTO_FOOTER);
    craftPacket(op);
  }
}

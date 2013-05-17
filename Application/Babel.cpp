//
// Babe.cpp for  in /home/champi_d//AdvancedCPP/Babel
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Tue Nov 15 16:46:16 2011 alexandre champion
// Last update Sun Dec  4 22:55:12 2011 alexandre champion
//

#include "Babel.hpp"
#include "UserConnectCmd.hpp"
#include "UserConnectionSucceededCmd.hpp"
#include "UserConnectionFailedCmd.hpp"
#include "UserStatusCmd.hpp"
#include "UpdateUserStatusCmd.hpp"
#include "AddContactCmd.hpp"
#include "ContactRequestCmd.hpp"
#include "AcceptContactRequestCmd.hpp"
#include "RejectContactRequestCmd.hpp"
#include "DeleteContactCmd.hpp"
#include "UnknownContactCmd.hpp"
#include "RequestCallCmd.hpp"
#include "CallRequestCmd.hpp"
#include "AcceptCallCmd.hpp"
#include "CallAcceptedCmd.hpp"
#include "RejectCallCmd.hpp"
#include "CallRejectedCmd.hpp"
#include "HangUpCallCmd.hpp"
#include "CallHungUpCmd.hpp"
#include "SuspendCallCmd.hpp"
#include "CallSuspendedCmd.hpp"
#include "ResumeCallCmd.hpp"
#include "CallResumedCmd.hpp"
#include "EndCallCmd.hpp"
#include "ErrorCmd.hpp"
#include "ConnectionLostCmd.hpp"
#include "SendTextCmd.hpp"
#include "ReceiveTextCmd.hpp"

Babel::Babel()
  : mApp(new Babe::ApplicationManager("Babel")),
    mCmdMgr(Babe::CommandManager::getSingletonPtr())
{
  registerCommands();
}

Babel::~Babel()
{ 
}

void	Babel::run()
{
  mApp->run();
}

void Babel::registerCommands()
{
  registerConnectionManagementCmds();
  registerUserStatusManagementCmds();
  registerContactManagementCmds();
  registerCallManagementCmds();
  registerErrorManagementCmds();
  registerTextManagementCmds();
}

/*
** Connection management
*/
void Babel::registerConnectionManagementCmds()
{
  mCmdMgr->registerCommand("userconnect", new Babe::CommandFromStringFactoryTpl<UserConnectCmd>,
			   std::string("userconnect userName userPassword\n") +
			   std::string("Command to be executed from the gui to inform the network of a new user connection."));
  mCmdMgr->registerCommand("userconnectionsucceeded", new Babe::CommandFromStringFactoryTpl<UserConnectionSucceededCmd>,
			   std::string("userconnectionsucceeded\n") +
			   std::string("Command to be executed from the network to inform the gui the connection succeeded."));
  mCmdMgr->registerCommand("userconnectionfailed", new Babe::CommandFromStringFactoryTpl<UserConnectionFailedCmd>,
			   std::string("userconnectionfailed errorMessage\n") +
			   std::string("Command to be executed from the network to inform the gui the connection failed along with an error message."));  
}

/*
** User status management
*/
void Babel::registerUserStatusManagementCmds()
{
  mCmdMgr->registerCommand("userstatus", new Babe::CommandFromStringFactoryTpl<UserStatusCmd>,
			   std::string("userstatus login status\n") +
			   std::string("Command to be executed from the network to inform the gui about a user status."));
  mCmdMgr->registerCommand("updateuserstatus", new Babe::CommandFromStringFactoryTpl<UpdateUserStatusCmd>,
			   std::string("updateuserstatus status\n") +
			   std::string("Command to be executed from the gui to inform the network the connected user changed his status."));  
}

/*
** Contact management
*/
void Babel::registerContactManagementCmds()
{
  mCmdMgr->registerCommand("addcontact", new Babe::CommandFromStringFactoryTpl<AddContactCmd>,
			   std::string("addcontact login\n") +
			   std::string("Command to be executed from the gui to inform the network the connected user wants to add a new contact."));
  mCmdMgr->registerCommand("contactrequest", new Babe::CommandFromStringFactoryTpl<ContactRequestCmd>,
			   std::string("contactrequest login\n") +
			   std::string("Command to be executed from the network to inform the gui a user wants to add the connected user as a new contact."));
  mCmdMgr->registerCommand("acceptcontactrequest", new Babe::CommandFromStringFactoryTpl<AcceptContactRequestCmd>,
			   std::string("acceptcontactrequest login\n") +
			   std::string("Command to be executed from the gui to inform the network the connected user accepted the contact request."));
  mCmdMgr->registerCommand("rejectcontactrequest", new Babe::CommandFromStringFactoryTpl<RejectContactRequestCmd>,
			   std::string("rejectcontactrequest login\n") +
			   std::string("Command to be executed from the gui to inform the network the connected user rejected the contact request."));
  mCmdMgr->registerCommand("deletecontact", new Babe::CommandFromStringFactoryTpl<DeleteContactCmd>,
			   std::string("deletecontact login\n") +
			   std::string("Command to be executed from the gui to inform the network the connected user wants to delete a contact."));  
  mCmdMgr->registerCommand("unknowncontact", new Babe::CommandFromStringFactoryTpl<UnknownContactCmd>,
			   std::string("unknwoncontact login\n") +
			   std::string("Command to be executed from the network to inform the gui the added contact does not exist."));
}

/*
** Call management
*/
void Babel::registerCallManagementCmds()
{
  mCmdMgr->registerCommand("requestcall", new Babe::CommandFromStringFactoryTpl<RequestCallCmd>,
			   std::string("requestcall login\n") +
			   std::string("Command to be executed from the gui to inform the network the connected user wants to call a contact."));
  mCmdMgr->registerCommand("callrequest", new Babe::CommandFromStringFactoryTpl<CallRequestCmd>,
			   std::string("callrequest login\n") +
			   std::string("Command to be executed from the network to inform the gui a contact wants to call the connected user."));
  mCmdMgr->registerCommand("acceptcall", new Babe::CommandFromStringFactoryTpl<AcceptCallCmd>,
			   std::string("acceptcall login\n") +
			   std::string("Command to be executed from the gui to inform the network the connected user has accepted the call.\n") +
			   std::string("This turns ON the AudioManager to start recording outgoing sound and playing incomming sound."));
  mCmdMgr->registerCommand("callaccepted", new Babe::CommandFromStringFactoryTpl<CallAcceptedCmd>,
			   std::string("callaccepted login\n") +
			   std::string("Command to be executed from the network to inform the gui the contact has accepted the call.\n") +
			   std::string("This turns ON the AudioManager to start recording outgoing sound and playing incomming sound."));
  mCmdMgr->registerCommand("rejectcall", new Babe::CommandFromStringFactoryTpl<RejectCallCmd>,
			   std::string("rejectcall login\n") +
			   std::string("Command to be executed from the gui to inform the network the connected user has rejected the call."));
  mCmdMgr->registerCommand("callrejected", new Babe::CommandFromStringFactoryTpl<CallRejectedCmd>,
			   std::string("callrejected login\n") +
			   std::string("Command to be executed from the network to inform the gui the contact has rejected the call."));
  mCmdMgr->registerCommand("hangupcall", new Babe::CommandFromStringFactoryTpl<HangUpCallCmd>,
			   std::string("hangupcall login\n") +
			   std::string("Command to be executed from the gui to inform the network the connected user has rejected the call.\n") +
			   std::string("This turns OFF the AudioManager to stop recording outgoing sound and playing incomming sound."));
  mCmdMgr->registerCommand("callhungup", new Babe::CommandFromStringFactoryTpl<CallHungUpCmd>,
			   std::string("callhungup login\n") +
			   std::string("Command to be executed from the network to inform the gui the contact hung up.\n") +
			   std::string("This turns OFF the AudioManager to stop recording outgoing sound and playing incomming sound."));
  mCmdMgr->registerCommand("suspendcall", new Babe::CommandFromStringFactoryTpl<SuspendCallCmd>,
			   std::string("suspendcall login\n") +
			   std::string("Command to be executed from the gui to inform the network the connected user has suspended the call.\n") +
			   std::string("This turns OFF the AudioManager to stop recording outgoing sound and playing incomming sound."));
  mCmdMgr->registerCommand("callsuspended", new Babe::CommandFromStringFactoryTpl<CallSuspendedCmd>,
			   std::string("callsuspended login\n") +
			   std::string("Command to be executed from the network to inform the gui the contact suspended the call.\n") +
			   std::string("This turns OFF the AudioManager to stop recording outgoing sound and playing incomming sound."));
  mCmdMgr->registerCommand("resumecall", new Babe::CommandFromStringFactoryTpl<ResumeCallCmd>,
			   std::string("resumecall login\n") +
			   std::string("Command to be executed from the gui to inform the network the connected user has resumed the call.\n") +
			   std::string("This turns ON the AudioManager to start recording outgoing sound and playing incomming sound."));
  mCmdMgr->registerCommand("callresumed", new Babe::CommandFromStringFactoryTpl<CallResumedCmd>,
			   std::string("callresumed login\n") +
			   std::string("Command to be executed from the network to inform the gui the contact resumed the call.\n") +
			   std::string("This turns ON the AudioManager to start recording outgoing sound and playing incomming sound."));
  mCmdMgr->registerCommand("endcall", new Babe::CommandFromStringFactoryTpl<EndCallCmd>,
			   std::string("endcall login\n") +
			   std::string("Command to be executed from the gui to put an end to a call without informing the network.\n") +
			   std::string("This turns OFF the AudioManager to stop recording outgoing sound and playing incomming sound."));
}
  
/*
** Error management
*/
void Babel::registerErrorManagementCmds()
{
  mCmdMgr->registerCommand("error", new Babe::CommandFromStringFactoryTpl<ErrorCmd>,
			   std::string("error errorMessage\n") +
			   std::string("Command to be executed from the network (or elsewhere) to inform the gui about an error."));
  mCmdMgr->registerCommand("connectionlost", new Babe::CommandFromStringFactoryTpl<ConnectionLostCmd>,
			   std::string("connectionlost\n") +
			   std::string("Command to be executed from the network to inform the gui the connection to the remote server was lost."));
}

/*
** Text management
*/
void Babel::registerTextManagementCmds()
{
  mCmdMgr->registerCommand("sendtext", new Babe::CommandFromStringFactoryTpl<SendTextCmd>,
			   std::string("sendtext login message\n") +
			   std::string("Command to be executed from the gui to send a message to the specified login.\n"));
  mCmdMgr->registerCommand("receivetext", new Babe::CommandFromStringFactoryTpl<ReceiveTextCmd>,
			   std::string("receivetext login message\n") +
			   std::string("Command to be executed from the network to inform the gui the connected user received a message from login."));
}

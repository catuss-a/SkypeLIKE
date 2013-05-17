
#include <iostream>
#include "BabeCommands.hpp"
#include "BabeLogManager.hpp"
#include "BabeStringUtils.hpp"

#include "BabeQuitCmd.hpp"
#include "BabeUndoCmd.hpp"
#include "BabeLoadPluginCmd.hpp"
#include "BabeUnloadPluginCmd.hpp"
#include "BabeConnectCmd.hpp"

namespace Babe
{

  Commands* Commands::getSingletonPtr()
  {
    return msSingleton;
  }

  Commands& Commands::getSingleton()
  {
    ASSERT_SINGLETON( msSingleton, "Commands", "getSingleton()" );  return ( *msSingleton );
  }

  Commands::Commands()
  {
    // Register Babe builtin commands
    registerCommand("quit", new CommandFromStringFactoryTpl<QuitCmd>,
		    std::string("quit\n") +
		    std::string("Exit the application in a proper way."));
    registerCommand("undo", new CommandFromStringFactoryTpl<UndoCmd>,
		    std::string("undo\n") +
		    std::string("Undo the last command."));
    registerCommand("loadplugin", new CommandFromStringFactoryTpl<LoadPluginCmd>,
		    std::string("loadplugin filePartName\n") +
		    std::string("Load a plugin. You have to specify only part of the file name.\n") +
		    std::string("eg. Babe_NinaNetwork for Babe_NinaNetwork.dll on windows or libBabe_NinaNetwork.so on linux"));
    registerCommand("unloadplugin", new CommandFromStringFactoryTpl<UnloadPluginCmd>,
		    std::string("unloadplugin filePartName\n") +
		    std::string("Unload a plugin. You have to specify only part of the file name.\n") +
		    std::string("eg. Babe_NinaNetwork for Babe_NinaNetwork.dll on windows or libBabe_NinaNetwork.so on linux"));
    registerCommand("connect", new CommandFromStringFactoryTpl<ConnectCmd>,
		    std::string("connect hostName port family\n") +
		    std::string("Connect to a remote server."));
  }

  Commands::~Commands()
  {
    for (CommandFactoryMap::iterator i = mCommands.begin(); i != mCommands.end(); ++i)
      delete i->second;
  }

  ICommand* Commands::fromStringToCmd(std::string const& command)
  {
    CommandParser::ParsedCommand pc = mParser.parseCommand(command);
    CommandFactoryMap::iterator found = mCommands.find(StringUtils::toLower(pc.name));
    if (found == mCommands.end())
      return 0;
    return found->second->create(pc.args);
  }

  void Commands::registerCommand(std::string const& commandName, CommandFromStringFactory* commandFactory, std::string const& man)
  {
    CommandFactoryMap::iterator found = mCommands.find(commandName);
    if (found != mCommands.end())
      {
	LOGE(commandName + " is already a registered command.");
	return ;
      }
    mCommands[commandName] = commandFactory;
    mCommandMans[commandName] = man;
  }

  void Commands::disableCommand(std::string const& command)
  {
    CommandFactoryMap::iterator i = mCommands.find(command);
    if (i == mCommands.end())
      {
	LOGE("Commands::disableCommand : No such command " + command);
	return ;
      }
    mCommands.erase(i);
    mDisabledCommands[command] = i->second;
    LOG("Commands::disableCommand : Command " + command + " disabled.");
  }

  void Commands::enableCommand(std::string const& command)
  {
    CommandFactoryMap::iterator i = mDisabledCommands.find(command);
    if (i == mDisabledCommands.end())
      {
	LOGE("Commands::enableCommand : No such command disabled " + command);
	return ;
      }
    mDisabledCommands.erase(i);
    mCommands[command] = i->second;
    LOG("Commands::enableCommand : Command " + command + " re-enabled.");
  }

  bool Commands::isRegistered(std::string const& command)
  {
    CommandParser::ParsedCommand pc = mParser.parseCommand(command);
    CommandFactoryMap::iterator found = mCommands.find(pc.name);
    if (found != mCommands.end())
      return true;
    return false;
  }

  bool Commands::isRegistered(ICommand* command)
  {
    CommandFactoryMap::iterator found = mCommands.find(command->getName());
    if (found != mCommands.end())
      return true;
    return false;
  }

  bool Commands::isDisabled(std::string const& command)
  {
    CommandParser::ParsedCommand pc = mParser.parseCommand(command);
    CommandFactoryMap::iterator found = mDisabledCommands.find(pc.name);
    if (found != mDisabledCommands.end())
      return true;
    return false;
  }

  bool Commands::isDisabled(ICommand* command)
  {
    CommandFactoryMap::iterator found = mDisabledCommands.find(command->getName());
    if (found != mDisabledCommands.end())
      return true;
    return false;
  }

  std::map<std::string, std::string> const& Commands::getCommandMans() const
  {
    return mCommandMans;
  }

} // End of namespace Babe

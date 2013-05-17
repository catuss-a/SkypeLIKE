
#include "BabeCommandManager.hpp"
#include "BabeLogManager.hpp"

namespace Babe
{
	CommandManager* CommandManager::getSingletonPtr()
	{
		return msSingleton;
	}

	CommandManager& CommandManager::getSingleton()
	{
        ASSERT_SINGLETON( msSingleton, "CommandManager", "getSingleton()" );  return ( *msSingleton );  
	}

  CommandManager::CommandManager()
    : System("CommandSystem"),
      mMaxUndoableCmd(10),
      mTimeOut(1 / 100.0f),
      mCommands(new Commands)
  {
    LOG("CommandManager created");
  }

  CommandManager::~CommandManager()
  {
    delete mCommands;
  }

  bool CommandManager::init()
  {
    LOG("CommandManager initialized");
    return true;
  }

  void CommandManager::shutdown()
  {
  }

  void CommandManager::update(float)
  {
    float localDt = 0;
    mClock->reset();
    ICommand* cmd;
    while (!mCommandQueue.empty() && localDt < mTimeOut)
      {
	cmd = mCommandQueue.front();
	mCommandQueue.pop_front();
	cmd->execute();
	if (cmd->isUndoable())
	  mCommandHistory.push_front(cmd);
	else
	  delete cmd;
	localDt = mClock->updateAndGetDeltaTime();
      }
    while (mCommandHistory.size() >= mMaxUndoableCmd)
      {
	cmd = mCommandHistory.back();
	mCommandHistory.pop_back();
	delete cmd;
      }
  }

  void CommandManager::execute(std::string const& command)
  {
    ICommand* cmd = mCommands->fromStringToCmd(command);
    if (cmd)
      {
	if (cmd->getPriority() == ICommand::LOW)
	  mCommandQueue.push_back(cmd);
	else if (cmd->getPriority() == ICommand::HIGH)
	  {
	    cmd->execute();
	    if (cmd->isUndoable())
	      mCommandHistory.push_front(cmd);
	    else
	      delete cmd;
	  }
      }
    else if (!mCommands->isDisabled(command))
      LOGE("Unknown command : \"" + command + "\"");
  }

  void CommandManager::execute(ICommand* command)
  {
    if (mCommands->isRegistered(command))
      {
	if (command->getPriority() == ICommand::LOW)
	  mCommandQueue.push_back(command);
	else if (command->getPriority() == ICommand::HIGH)
	  {
	    command->execute();
	    if (command->isUndoable())
	      mCommandHistory.push_front(command);
	    else
	      delete command;
	  }
      }
    else if (!mCommands->isDisabled(command))
      LOGE("Cannot execute unregistered command : \"" + command->getName() + "\". To register it simply call Babe::CommandManager::getSingletonPtr()->registerCommand(\"" + command->getName() + "\", CommandFromStringFactoryTpl< [the type of \"" + command->getName() + "\"] >);");
  }

  void CommandManager::registerCommand(std::string const& commandName, CommandFromStringFactory* commandFactory, std::string const& man)
  {
    mCommands->registerCommand(commandName, commandFactory, man);
  }

  void CommandManager::disableCommand(std::string const& command)
  {
    mCommands->disableCommand(command);
  }

  void CommandManager::enableCommand(std::string const& command)
  {
    mCommands->enableCommand(command);
  }

  bool CommandManager::undo()
  {
    if (!mCommandHistory.empty())
      {
	ICommand* cmd = mCommandHistory.front();
	mCommandHistory.pop_front();
	cmd->unexecute();
	delete cmd;
      }
    return false;
  }

  bool CommandManager::redo() // TODO
  {
    return false;
  }

  void CommandManager::setMaxUndoableCmd(size_t max)
  {
    mMaxUndoableCmd = max;
  }

  std::string const& CommandManager::getReturnMessage() const
  {
    return mReturnMessage;
  }

  void CommandManager::setReturnMessage(std::string const& message)
  {
    LOG("CommandManager : return message [" + message + "]");
    mReturnMessage = message;
  }

} // End of namespace Babe

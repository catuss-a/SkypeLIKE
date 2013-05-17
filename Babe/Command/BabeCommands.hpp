
#ifndef		__BABE_COMMANDS_HPP__
# define	__BABE_COMMANDS_HPP__

# include <map>
# include <string>
# include "BabeDef.hpp"
# include "BabeSingleton.hpp"
# include "BabeICommand.hpp"
# include "BabeCommandParser.hpp"

namespace Babe
{

  class BABE_DLLREQ Commands : public Singleton<Commands>
  {
  public:
    Commands();
    virtual ~Commands();
    ICommand* fromStringToCmd(std::string const& command);
    void registerCommand(std::string const& commandName, CommandFromStringFactory* commandFactory, std::string const& man);
    void disableCommand(std::string const& command);
    void enableCommand(std::string const& command);
    bool isRegistered(std::string const& command);
    bool isRegistered(ICommand* command);
    bool isDisabled(std::string const& command);
    bool isDisabled(ICommand* command);
    static Commands* getSingletonPtr();
    static Commands& getSingleton();
    std::map<std::string, std::string> const& getCommandMans() const;

  private:
    typedef std::map<std::string, CommandFromStringFactory*> CommandFactoryMap;
    typedef std::map<std::string, std::string> CommandManMap;
    CommandFactoryMap  	mCommands;
    CommandFactoryMap  	mDisabledCommands;
    CommandParser	mParser;
    CommandManMap	mCommandMans;
  };

} // End of namespace Babe

#endif		// ! __BABE_COMMANDS_HPP__

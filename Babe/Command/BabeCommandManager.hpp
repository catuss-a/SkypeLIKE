
#ifndef		__BABE_COMMANDMANAGER_HPP__
# define	__BABE_COMMANDMANAGER_HPP__

# include <deque>
# include <string>
# include "BabeDef.hpp"
# include "BabeSingleton.hpp"
# include "BabeSystem.hpp"
# include "BabeCommands.hpp"

namespace Babe
{

  class BABE_DLLREQ CommandManager : public Singleton<CommandManager>, public System
  {
  public:
    CommandManager();
    virtual ~CommandManager();
    virtual bool init();
    virtual void shutdown();
    virtual void update(float dt);
    virtual void setImpl(SystemImpl*) {}
    virtual void unsetImpl() {}
    void execute(std::string const& command);
    void execute(ICommand* command);
    void registerCommand(std::string const& commandName, CommandFromStringFactory* commandFactory, std::string const& man);
    void disableCommand(std::string const& command);
    void enableCommand(std::string const& command);
    bool undo();
    bool redo();
    void setMaxUndoableCmd(size_t max);
    std::string const& getReturnMessage() const;
    void setReturnMessage(std::string const& message);
	static CommandManager* getSingletonPtr();
	static CommandManager& getSingleton();

  private:
    typedef std::deque<ICommand*> CommandQueue;
    CommandQueue	mCommandQueue;
    CommandQueue	mCommandHistory;
    size_t		mMaxUndoableCmd;
    float		mTimeOut;
    Commands*		mCommands;
    std::string		mReturnMessage;
  };

} // End of namespace Babe

#endif		// ! __BABE_COMMANDMANAGER_HPP__

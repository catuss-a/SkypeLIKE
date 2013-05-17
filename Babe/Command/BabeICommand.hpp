
#ifndef		__BABE_ICOMMAND_HPP__
# define	__BABE_ICOMMAND_HPP__

# include "BabeDef.hpp"
# include "BabeCommandParser.hpp"
# include "BabeNonCopyable.hpp"
# include "BabeLogManager.hpp"

namespace Babe
{

  /*
  ** Derived class MUST HAVE a default constructor AND a construtor like the following :
  ** derivedFromICommand(CommandParser::ArgVector& args);
  */
  class BABE_DLLREQ ICommand
  {
  public:
    enum ePriority
    {
      HIGH,
      LOW
    };

  public:
    ICommand(ePriority priority = LOW) : mPriority(priority) {}
    virtual ~ICommand() {}
    void execute() { LOGCMD(stringify()); exec(); }
    virtual void exec() = 0;
    void unexecute() { LOGCMD("[UNEXECUTE] " + stringify()); unexec(); }
    virtual void unexec() {}
    virtual bool isUndoable() const { return false; }
    virtual std::string const& getName() const = 0;
    virtual std::string const& stringify() { return getName(); }
    ePriority getPriority() const { return mPriority; }
    void setPriority(ePriority priority) { mPriority = priority; }

  protected:
    ePriority mPriority;
  };

  class BABE_DLLREQ CommandFromStringFactory : public NonCopyable
  {
  public:
    virtual ICommand* create(CommandParser::ArgVector&) = 0;
  };

  template <class TCommand>
  class CommandFromStringFactoryTpl : public CommandFromStringFactory
  {
    virtual ICommand* create(CommandParser::ArgVector& args)
    {
      return new TCommand(args);
    }
  };

} // End of namespace Babe

#endif		// ! __BABE_ICOMMAND_HPP__

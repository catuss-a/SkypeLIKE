
#ifndef		__BABE_COMMANDPARSER_HPP__
# define	__BABE_COMMANDPARSER_HPP__

# include <deque>
# include <string>
# include "BabeDef.hpp"

namespace Babe
{

  class BABE_DLLREQ CommandParser
  {
  public:
    typedef std::deque<std::string> ArgVector;
    struct ParsedCommand
    {
      std::string	name;
      ArgVector		args;
    };

  public:
    CommandParser();
    virtual ~CommandParser();
    ParsedCommand parseCommand(std::string const& command);
  };

} // End of namespace Babe

#endif		// ! __BABE_COMMANDPARSER_HPP__

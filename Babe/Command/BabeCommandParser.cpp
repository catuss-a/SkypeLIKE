
#include <iostream>
#include <sstream>
#include <iterator>
#include "BabeCommandParser.hpp"

namespace Babe
{

  CommandParser::CommandParser()
  {
  }

  CommandParser::~CommandParser()
  { 
  }

  CommandParser::ParsedCommand CommandParser::parseCommand(std::string const& command)
  {
    ParsedCommand pc;
    std::istringstream istr(command);
    std::istream_iterator<std::string> end;
    std::istream_iterator<std::string> i(istr);
    if (i != end)
      pc.name = (*i);
    ++i;
    for (; i != end ;++i)
      pc.args.push_back(*i);
    return pc;
  }

} // End of namespace Babe

//
// BabeStringUtils.cpp for  in /home/champi_d//AdvancedCPP/Babel/Babe
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Nov 13 19:56:20 2011 alexandre champion
// Last update Sun Nov 13 19:57:06 2011 alexandre champion
//

#include <algorithm>
#include <sstream>
#include "BabeStringUtils.hpp"

namespace Babe
{

  StringUtils::StringUtils()
  {
  }

  StringUtils::~StringUtils()
  {
  }

  std::string StringUtils::toLower(std::string const& str)
  {
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    return lower;
  }

  std::string StringUtils::toUpper(std::string const& str)
  {
    std::string lower = str;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::toupper);
    return lower;
  }

  float StringUtils::toFloat(std::string const& str)
  {
    std::istringstream i(str);
    float x;
    if (!(i >> x))
      return 0;
    return x;
  }

  unsigned int StringUtils::toUInt(std::string const& str)
  {
    std::istringstream i(str);
    unsigned int x;
    if (!(i >> x))
      return 0;
    return x;
  }

  std::string StringUtils::cutEnd(std::string const& str, std::string const& end)
  {
    std::string s = str;
    size_t pos = s.find(end);
    return s.substr(0, pos);
  }

  std::string StringUtils::spaceToUnderscore(std::string const& str)
  {
    std::string s = str;
    size_t i;
    while ((i = s.find(' ')) != std::string::npos)
      s.replace(i, 1, "_");
    return s;
  }

} // End of namespace Babe

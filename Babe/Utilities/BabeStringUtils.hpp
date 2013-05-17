//
// BabeStringUtils.hpp for  in /home/champi_d//AdvancedCPP/Babel/Babe
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Nov 13 19:56:11 2011 alexandre champion
// Last update Sun Nov 13 19:56:39 2011 alexandre champion
//

#ifndef		__BABE_STRINGUTILS_HPP__
# define	__BABE_STRINGUTILS_HPP__

# include <sstream>
# include <string>
# include "BabeDef.hpp"

namespace Babe
{

  class BABE_DLLREQ StringUtils
  {
  private:
    StringUtils();
    ~StringUtils();

  public:
    static std::string toLower(std::string const& str);
    static std::string toUpper(std::string const& str);
    template<typename T>
    static std::string fromNum(T n);
    static float toFloat(std::string const& str);
    static unsigned int toUInt(std::string const& str);
    static std::string cutEnd(std::string const& str, std::string const& end);
    static std::string spaceToUnderscore(std::string const& str);
  };

  template<typename T>
  std::string StringUtils::fromNum(T n)
  {
    std::stringstream ss;
    ss << n;
    return ss.str();
  }

} // End of namespace Babe

#endif		// ! __BABE_STRINGUTILS_HPP__

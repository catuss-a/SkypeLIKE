
#ifndef		__BABE_SYSTEMFACTORIES_HPP__
# define	__BABE_SYSTEMFACTORIES_HPP__

# include <string>
# include <map>
# include "BabeDef.hpp"
# include "BabeSystem.hpp"

namespace Babe
{

  class BABE_DLLREQ SystemFactories
  {
  public:
    SystemFactories();
    ~SystemFactories();
    System* createSystem(std::string const& systemName);

  private:
    typedef std::map<std::string, SystemFactory*> SystemFactoryMap;
    SystemFactoryMap mFactories;
  };

} // End of namespace Babe

#endif		// ! __BABE_SYSTEMFACTORIES_HPP__

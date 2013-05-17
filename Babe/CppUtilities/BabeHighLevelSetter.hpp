
#ifndef		__BABE_HIGHTLEVELSETTER_HPP__
# define	__BABE_HIGHTLEVELSETTER_HPP__

# include <map>
# include <string>
# include "BabeDef.hpp"

namespace Babe
{

  class BABE_DLLREQ HighLevelSetter
  {
  public:
    bool setHighLevelData(std::string const& dataName, void* data);

  protected:
    HighLevelSetter();
    virtual ~HighLevelSetter();

  protected:
    typedef bool (HighLevelSetter::*SetData)(void* data);
    typedef std::map<std::string, SetData> SetDataMap;
    SetDataMap	mSetDataFuncs;
  };

} // End of namespace Babe

#endif		// ! __BABE_HIGHTLEVELSETTER_HPP__


#include "BabeHighLevelSetter.hpp"
#include "BabeLogManager.hpp"

namespace Babe
{

  HighLevelSetter::HighLevelSetter()
  {
  }

  HighLevelSetter::~HighLevelSetter()
  {
  }

  bool HighLevelSetter::setHighLevelData(std::string const& dataName, void* data)
  {
    SetDataMap::iterator i = mSetDataFuncs.find(dataName);
    if (i == mSetDataFuncs.end())
      {
	LOGE("No such data to set : " + dataName);
	return false;
      }
    SetData setData = i->second;
    return (this->*setData)(data);
  }

} // End of namespace Babe

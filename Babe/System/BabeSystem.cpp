
#include "BabeSystem.hpp"
#include "BabeApplicationSettings.hpp"

namespace Babe
{
  
  System::System(std::string const& name, float targetRate, int initOrdering, int runOrdering)
    : mName(name),
      mPluginName("dummy"),
      mTargetRate(targetRate),
      mCurrentDt(0),
      mInitOrdering(initOrdering),
      mRunOrdering(runOrdering)
  {
    mClock = new Clock(targetRate);
  }

  System::~System()
  {
  }

  void System::setPluginName(std::string const& pluginName)
  {
    mPluginName = pluginName;
  }

  std::string const& System::getPluginName() const
  {
    return mPluginName;
  }

  void System::updateTargetRate(float dt)
  {
    mCurrentDt += dt;
    if (mCurrentDt >= mTargetRate)
      {
	update(mCurrentDt);
	mCurrentDt = 0;
	//mCurrentDt -= mTargetRate;
      }
  }

  std::string const& System::getName() const
  {
    return mName;
  }

  void System::setTargetRate(float targetRate)
  {
    mTargetRate = targetRate;
    mClock->setTargetRate(targetRate);
  }

  void System::setInitOrdering(int initOrdering)
  {
    mInitOrdering = initOrdering;
  }

  int System::getInitOrdering() const
  {
    return mInitOrdering;
  }

  void System::setRunOrdering(int runOrdering)
  {
    mRunOrdering = runOrdering;
  }

  int System::getRunOrdering() const
  {
    return mRunOrdering;
  }

} // End of namespace Babe

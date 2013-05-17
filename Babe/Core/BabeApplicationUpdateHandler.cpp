
#include <algorithm>
#include "BabeLogManager.hpp"
#include "BabeApplicationUpdateHandler.hpp"
#include "BabeSystemManager.hpp"

namespace Babe
{
  ApplicationUpdateHandler::ApplicationUpdateHandler(float targetRate)
    : mRunning(false),
      mTargetRate(targetRate),
      mElapsed(0.0f),
      mFpsCount(0),
      mFps(static_cast<int>(1.0f / targetRate))
  {
    mClock = new Clock(targetRate);
    LOG("ApplicationUpdateHandler created");
  }
  
  ApplicationUpdateHandler::~ApplicationUpdateHandler()
  { 
    LOG("Destroying ApplicationUpdateHandler...");
    delete mClock;
  }

  void		ApplicationUpdateHandler::run()
  {
    float dt = mTargetRate;
    mClock->reset();
    mRunning = true;
    //LogManager::getSingletonPtr()->setIsActive(false);
    while (mRunning)
      {
	for (SystemVector::iterator i = mSystems.begin(); i != mSystems.end(); ++i)
	  (*i)->updateTargetRate((*i)->mClock->updateAndGetDeltaTime(dt));
	dt = mClock->updateAndGetDeltaTime();
	computeFps(dt);
#ifdef	NDEBUG
	if (dt > 1.0f / 10.0f)
	  dt = mTargetRate;
#endif
      }
    //LogManager::getSingletonPtr()->setIsActive(true);
    SystemManager::getSingletonPtr()->shutdownSystems();
  }

  void		ApplicationUpdateHandler::runFrame()
  {
    if (!mRunning)
      return ;
    static float dt = mTargetRate;
    for (SystemVector::iterator i = mSystems.begin(); i != mSystems.end(); ++i)
      (*i)->updateTargetRate((*i)->mClock->updateAndGetDeltaTime(dt));
    dt = mClock->updateAndGetDeltaTime();
    computeFps(dt);
#ifdef	NDEBUG
    if (dt > 1.0f / 10.0f)
      dt = mTargetRate;
#endif
    if (!mRunning)
      SystemManager::getSingletonPtr()->shutdownSystems();
  }

  void		ApplicationUpdateHandler::runFrame(float dt)
  {
    if (!mRunning)
      return ;
#ifdef	NDEBUG
    if (dt > 1.0f / 1.0f)
      dt = mTargetRate;
#endif
    for (SystemVector::iterator i = mSystems.begin(); i != mSystems.end(); ++i)
      (*i)->updateTargetRate((*i)->mClock->updateAndGetDeltaTime(dt));
    computeFps(dt);
    if (!mRunning)
      SystemManager::getSingletonPtr()->shutdownSystems();
  }

  bool		ApplicationUpdateHandler::stop()
  {
    if (mRunning)
      mRunning = false;
    else
      return false;
    return true;
  }

  void		ApplicationUpdateHandler::registerSystem(System* system)
  {
    SystemMap::iterator found = mRegisteredSystems.find(system->getName());
    if (found != mRegisteredSystems.end())
      return ;
    mSystems.push_back(system);
    mRegisteredSystems[system->getName()] = system;
    LOG(system->getName() + " registered to the ApplicationUpdateHandler.");
  }

  void		ApplicationUpdateHandler::unregisterSystem(System* system)
  {
    SystemMap::iterator found = mRegisteredSystems.find(system->getName());
    if (found == mRegisteredSystems.end())
      return ;
    SystemVector::iterator i = find(mSystems.begin(), mSystems.end(), system);
    if (i != mSystems.end())
      mSystems.erase(i);
  }

  Clock*	ApplicationUpdateHandler::getClock() const
  {
    return mClock;
  }

  bool		ApplicationUpdateHandler::isRunning() const
  {
    return mRunning;
  }

  void		ApplicationUpdateHandler::setToRunning()
  {
    mRunning = true;
  }

  int		ApplicationUpdateHandler::getFps() const
  {
    return mFps;
  }

  void		ApplicationUpdateHandler::setTargetRate(float targetRate)
  {
    mTargetRate = targetRate;
    /// limit target rate from 5fps to 30fps
    if (mTargetRate > 0.2f)
      mTargetRate = 0.2f;
    else if (mTargetRate < 0.033f)
      mTargetRate = 0.033f;
  }

  float		ApplicationUpdateHandler::getTargetRate() const
  {
    return mTargetRate;
  }

  void		ApplicationUpdateHandler::computeFps(float dt)
  {
    mElapsed += dt;
    mFpsCount++;
    if (mElapsed >= 1.0f)
      {
	mElapsed = 0;
	mFps = mFpsCount;
	mFpsCount = 0;
      }
  }

} // End of namespace Babe

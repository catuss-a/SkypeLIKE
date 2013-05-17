//
// BabeClock.cpp for  in /home/champi_d//AdvancedCPP/Babel/Babe
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Nov 13 19:49:00 2011 alexandre champion
// Last update Sun Nov 13 19:51:11 2011 alexandre champion
//

#include "BabeClock.hpp"

namespace Babe
{

  Clock::Clock(float targetRate)
    : mTimeScale(1.0f),
      mIsPaused(false),
      mTargetRate(targetRate)
  {
    reset();
  }

  Clock::~Clock(void)
  {
  }

  void Clock::reset(void)
  {
    mStartClock = clock();
    mLastClock = clock();
  }

  float Clock::updateAndGetDeltaTime(void)
  {
    float dt = 0;

    if (!mIsPaused)
      {
	clock_t nowClock = clock();
	dt = ((float)(nowClock - mLastClock) / (float)CLOCKS_PER_SEC) * mTimeScale;
	mLastClock = nowClock;
      }
    return dt;
  }

  float Clock::updateAndGetDeltaTime(float dtReal)
  {
    float dt = 0;

    if (!mIsPaused)
      dt = dtReal * mTimeScale;
    return dt;
  }

  void Clock::setPaused(bool isPaused)
  {
    mIsPaused = isPaused;
  }

  bool Clock::isPaused() const
  {
    return mIsPaused;
  }

  void Clock::setTimeScale(float scale)
  {
    mTimeScale = scale;
  }

  float Clock::getTimeScale() const
  {
    return mTimeScale;
  }

  float Clock::singleStep()
  {
    float dt = 0;

    if (mIsPaused)
      dt = mTargetRate * mTimeScale;
    return dt;
  }

  void Clock::setTargetRate(float targetRate)
  {
    mTargetRate = targetRate;
  }

} // End of namespace Babex

//
// BabeClock.hpp for  in /home/champi_d//AdvancedCPP/Babel/Babe
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Nov 13 19:48:49 2011 alexandre champion
// Last update Sun Nov 13 19:51:05 2011 alexandre champion
//

#ifndef		__BABE_CLOCK_HPP__
# define	__BABE_CLOCK_HPP__

# include <time.h>
# include "BabeDef.hpp"

namespace Babe
{

  class BABE_DLLREQ Clock
  {
  public:
    explicit Clock(float targetRate = 1.0f / 30.0f);
    ~Clock();
    void reset();
    float updateAndGetDeltaTime();
    float updateAndGetDeltaTime(float dtReal);
    void setPaused(bool isPaused);
    bool isPaused() const;
    void setTimeScale(float scale);
    float getTimeScale() const;
    float singleStep();
    void setTargetRate(float targetRate);

  private:
    clock_t                 mStartClock;
    clock_t                 mLastClock;
    float                   mTimeScale;
    bool                    mIsPaused;
    float                   mTargetRate;
  };

} // End of namespace Babe

#endif		// ! __BABE_CLOCK_HPP__

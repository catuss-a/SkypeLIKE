
#ifndef		__BABE_APPLICATIONUPDATEHANDLER_HPP__
# define	__BABE_APPLICATIONUPDATEHANDLER_HPP__

# include <vector>
# include "BabeDef.hpp"
# include "BabeSingleton.hpp"
# include "BabeClock.hpp"
# include "BabeSystem.hpp"

# if defined BABE_WIN32
//disable warnings on extern before template instantiation
# pragma warning (disable : 4231)

// STL forward declaration as expected for dll processing
// see http://support.microsoft.com/kb/168958/en-us
//BABE_EXTERN template class BABE_DLLREQ std::vector<Babe::System*>;
//BABE_EXTERN template class BABE_DLLREQ std::map<std::string, Babe::System*>;
# endif // ! BABE_WIN32

namespace Babe
{

  class BABE_DLLREQ ApplicationUpdateHandler : public Singleton<ApplicationUpdateHandler>
  {
  public:
    ApplicationUpdateHandler(float targetRate = 1.0f / 30.0f);
    ~ApplicationUpdateHandler();
    void run();
    void runFrame();
    void runFrame(float dt);
    bool stop();
    void registerSystem(System* system);
    void unregisterSystem(System* system);
    Clock* getClock() const;
    bool isRunning() const;
    void setToRunning();
    int getFps() const;
    void setTargetRate(float targetRate);
    float getTargetRate() const;

  private:
    void computeFps(float dt);

  private:
    typedef std::vector<System*> SystemVector;
    typedef std::map<std::string, System*> SystemMap;
    bool		mRunning;
    Clock*		mClock;
    float		mTargetRate;
    SystemVector	mSystems;
    float		mElapsed;
    int			mFpsCount;
    int			mFps;
    SystemMap		mRegisteredSystems;
  };

} // End of namespace Babe

#endif		// ! __BABE_APPLICATIONUPDATEHANDLER_HPP__

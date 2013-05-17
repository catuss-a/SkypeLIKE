
#ifndef		__BABE_SYSTEM_HPP__
# define	__BABE_SYSTEM_HPP__

# include <string>
# include "BabeDef.hpp"
# include "BabeNonCopyable.hpp"
# include "BabeClock.hpp"
# include "BabeHighLevelSetter.hpp"
# include "BabeSystemImpl.hpp"

namespace Babe
{

  class BABE_DLLREQ System : public NonCopyable, public HighLevelSetter
  {
  public:
    System(std::string const& name, float targetRate = 0, int initOrdering = -1, int runOrdering = -1);
    virtual ~System();
    virtual bool init() = 0;
    virtual void shutdown() = 0;
    virtual void update(float dt) = 0;
    virtual void setImpl(SystemImpl* impl) = 0;
    virtual void unsetImpl() = 0;
    void setPluginName(std::string const& pluginName);
    std::string const& getPluginName() const;
    void updateTargetRate(float dt);
    std::string const& getName() const;
    void setTargetRate(float targetRate);
    void setInitOrdering(int initOrdering);
    int getInitOrdering() const;
    void setRunOrdering(int runOrdering);
    int getRunOrdering() const;

  protected:
    std::string		mName;
    std::string		mPluginName;

  private:
    float		mTargetRate;
    float		mCurrentDt;
    int			mInitOrdering;
    int			mRunOrdering;

  public:
    Clock*		mClock;
  };

  class BABE_DLLREQ SystemFactory : public NonCopyable
  {
  public:
    virtual System* createSystem() = 0;
  };

  template <class TSystem>
  class BABE_DLLREQ SystemFactoryTpl : public SystemFactory
  {
    virtual System* createSystem()
    {
      return new TSystem;
    }
  };

} // End of namespace Babe

#endif		// ! __BABE_SYSTEM_HPP__


#ifndef		__BABE_CODECMANAGER_HPP__
# define	__BABE_CODECMANAGER_HPP__

# include "BabeDef.hpp"
# include "BabeSingleton.hpp"
# include "BabeSystem.hpp"
# include "BabeCodecManagerImpl.hpp"

namespace Babe
{

  class BABE_DLLREQ CodecManager : public Singleton<CodecManager>, public System
  {
  public:
    CodecManager();
    virtual ~CodecManager();
    virtual bool init();
    virtual void shutdown();
    virtual void update(float dt);
    virtual void setImpl(SystemImpl* impl);
    virtual void unsetImpl();
    void encode(void * iFrame, void *oFrame);
    void *decode(void * iFrame);
    static CodecManager* getSingletonPtr();
    static CodecManager& getSingleton();

  private:
    CodecManagerDummyImpl	mDummyImpl;
    CodecManagerImpl*		mImpl;
  };

} // End of namespace Babe

#endif		// ! __BABE_CODECMANAGER_HPP__

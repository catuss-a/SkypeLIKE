
#ifndef		__BABE_CODECMANAGERIMPL_HPP__
# define	__BABE_CODECMANAGERIMPL_HPP__

# include "BabeDef.hpp"
# include "BabeSystemImpl.hpp"
# include "BabeLogManager.hpp"

namespace Babe
{
  
  class BABE_DLLREQ CodecManagerImpl : public SystemImpl
  {
  public:
    virtual ~CodecManagerImpl() {}
    virtual bool init() = 0;
    virtual void shutdown() = 0;
    virtual void update(float dt) = 0;    
    virtual void encode(void * iFrame, void *oFrame) = 0;
    virtual void *decode(void * iFrame) = 0;
  };

  class BABE_DLLREQ CodecManagerDummyImpl : public CodecManagerImpl
  {
  public:
    CodecManagerDummyImpl() {}
    virtual ~CodecManagerDummyImpl() {}
    virtual bool init() { LOG("CodecManagerDummyImpl initialized"); return true; }
    virtual void shutdown() {}
    virtual void update(float) {}
    virtual void encode(void *, void *) {}
    virtual void *decode(void *) { return 0;}
  };

} // End of namespace Babe

#endif		// ! __BABE_CODECMANAGERIMPL_HPP__

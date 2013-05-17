
#ifndef		__BABE_AUDIOMANAGERIMPL_HPP__
# define	__BABE_AUDIOMANAGERIMPL_HPP__

# include "BabeDef.hpp"
# include "BabeSystemImpl.hpp"
# include "BabeLogManager.hpp"
# include "BabeAudioFrame.hpp"

namespace Babe
{
  
  class BABE_DLLREQ AudioManagerImpl : public SystemImpl
  {
  public:
    virtual ~AudioManagerImpl() {}
    virtual bool init() = 0;
    virtual void shutdown() = 0;
    virtual void update(float dt) = 0;    
    virtual void on() = 0;
    virtual void off() = 0;
    virtual AudioFrame* recordAudioFrame() = 0;
    virtual void playAudioFrame(AudioFrame* frame) = 0;
    virtual void playAudioFrame(char const* frame, size_t sizeFrame) = 0;
  };

  class BABE_DLLREQ AudioManagerDummyImpl : public AudioManagerImpl
  {
  public:
    AudioManagerDummyImpl() {}
    virtual ~AudioManagerDummyImpl() {}
    virtual bool init() { LOG("AudioManagerDummyImpl initialized"); return true; }
    virtual void shutdown() {}
    virtual void update(float) {}
    virtual void on() {}
    virtual void off() {}
    virtual AudioFrame* recordAudioFrame() { return 0; }
    virtual void playAudioFrame(AudioFrame*) {}
    virtual void playAudioFrame(char const*, size_t) {}
  };

} // End of namespace Babe

#endif		// ! __BABE_AUDIOMANAGERIMPL_HPP__

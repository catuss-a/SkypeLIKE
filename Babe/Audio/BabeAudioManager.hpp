
#ifndef		__BABE_AUDIOMANAGER_HPP__
# define	__BABE_AUDIOMANAGER_HPP__

# include "BabeDef.hpp"
# include "BabeSingleton.hpp"
# include "BabeSystem.hpp"
# include "BabeAudioManagerImpl.hpp"
# include "BabeAudioFrame.hpp"

namespace Babe
{

  class BABE_DLLREQ AudioManager : public Singleton<AudioManager>, public System
  {
  public:
    AudioManager();
    virtual ~AudioManager();
    virtual bool init();
    virtual void shutdown();
    virtual void update(float dt);
    void on();
    void off();
    AudioFrame* recordAudioFrame();
    void playAudioFrame(AudioFrame* frame);
    void playAudioFrame(char const* frame, size_t frameSize);
    void setAudioRawFrameSize(size_t size);
    void setAudioEncFrameSize(size_t size);
    size_t getAudioRawFrameSize() const;
    size_t getAudioEncFrameSize() const;
    virtual void setImpl(SystemImpl* impl);
    virtual void unsetImpl();
    static AudioManager* getSingletonPtr();
    static AudioManager& getSingleton();

  private:
    AudioManagerDummyImpl	mDummyImpl;
    AudioManagerImpl*		mImpl;
    size_t			mAudioRawFrameSize;
    size_t			mAudioEncFrameSize;
  };

} // End of namespace Babe

#endif		// ! __BABE_AUDIOMANAGER_HPP__

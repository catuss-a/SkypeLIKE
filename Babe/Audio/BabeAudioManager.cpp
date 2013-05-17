
#include "BabeAudioManager.hpp"
#include "BabeLogManager.hpp"

namespace Babe
{
  AudioManager* AudioManager::getSingletonPtr()
  {
    return msSingleton;
  }

  AudioManager& AudioManager::getSingleton()
  {
    ASSERT_SINGLETON( msSingleton, "AudioManager", "getSingleton()" );  return ( *msSingleton );  
  }

  AudioManager::AudioManager()
    : System("AudioSystem"),
      mAudioRawFrameSize(0),
      mAudioEncFrameSize(0)
  {
    mImpl = &mDummyImpl;
    LOG("AudioManager created");
  }

  AudioManager::~AudioManager()
  {
  }

  bool AudioManager::init()
  {
    return mImpl->init();
  }

  void AudioManager::shutdown()
  {
    mImpl->shutdown();
  }

  void AudioManager::update(float dt)
  {
    mImpl->update(dt);
  }

  void AudioManager::on()
  {
    mImpl->on();
  }

  void AudioManager::off()
  {
    mImpl->off();
  }

  AudioFrame* AudioManager::recordAudioFrame()
  {
    return mImpl->recordAudioFrame();
  }

  void AudioManager::playAudioFrame(AudioFrame* frame)
  {
    mImpl->playAudioFrame(frame);
  }

  void AudioManager::playAudioFrame(char const* frame, size_t frameSize)
  {
    mImpl->playAudioFrame(frame, frameSize);
  }

  void AudioManager::setAudioEncFrameSize(size_t size)
  {
    mAudioEncFrameSize = size;
  }

  void AudioManager::setAudioRawFrameSize(size_t size)
  {
    mAudioRawFrameSize = size;
  }

  size_t AudioManager::getAudioEncFrameSize() const
  {
    return mAudioEncFrameSize;
  }

  size_t AudioManager::getAudioRawFrameSize() const
  {
    return mAudioRawFrameSize;
  }

  void AudioManager::setImpl(SystemImpl* impl)
  {
    if (impl)
      {
	if (!(mImpl = dynamic_cast<AudioManagerImpl*>(impl)))
	  {
	    LOGE("AudioManager::setImpl the implementation is not a AudioManagerImpl*");
	    mImpl = &mDummyImpl;
	  }
      }
  }

  void AudioManager::unsetImpl()
  {
    mImpl = &mDummyImpl;
  }

} // End of namespace Babe

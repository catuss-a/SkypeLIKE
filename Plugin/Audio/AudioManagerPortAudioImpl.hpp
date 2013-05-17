
#ifndef		__AUDIOMANAGERPORTAUDIOIMPL_HPP__
# define	__AUDIOMANAGERPORTAUDIOIMPL_HPP__

# include <portaudio.h>
# include <queue>
# include <Babe.hpp>
# include "PortAudioFrame.hpp"

class BABE_DLLREQ AudioManagerPortAudioImpl : public Babe::AudioManagerImpl
{
 public:
  typedef std::queue<PortAudio::PortAudioFrame*> QueueFrames;
  enum eAudioType { INPUT = 1, OUTPUT };

 public:
  AudioManagerPortAudioImpl(int sampleRate = PortAudio::PortAudioFrame::SAMPLE_RATE,
			    int frameSize = PortAudio::PortAudioFrame::FRAME_SIZE);
  virtual ~AudioManagerPortAudioImpl();
  virtual bool init();
  virtual void shutdown();
  virtual void update(float dt);
  virtual void on();
  virtual void off();
  virtual Babe::AudioFrame* recordAudioFrame();
  virtual void playAudioFrame(Babe::AudioFrame* frame);
  virtual void playAudioFrame(char const* frame, size_t frameSize = PortAudio::PortAudioFrame::ENC_FRAME_SIZE);

 private:
  int StartRecord(const void *, void *, unsigned long,
		  const PaStreamCallbackTimeInfo*,
		  PaStreamCallbackFlags);
  int StartVoice(const void *, void *, unsigned long,
		 const PaStreamCallbackTimeInfo*,
		 PaStreamCallbackFlags);
  static int CallBack(const void *, void *, unsigned long,
		      const PaStreamCallbackTimeInfo*,
		      PaStreamCallbackFlags, void *);
  bool OpenStream(eAudioType type);
  bool SetParameters(PaStreamParameters*,
		     PaDeviceIndex,
		     int chanCount = PortAudio::PortAudioFrame::CHAN_COUNT,
		     PaSampleFormat spFormat = PortAudio::PortAudioFrame::SAMPLE_FORMAT,
		     void *hostAPI = 0);

 private:
  bool			mIsOn;
  PaStreamParameters	mOParameters;
  PaStreamParameters	mIParameters;
  PaStream*		mOStream;
  PaStream*		mIStream;
  int			mSampleRate;
  int			mFrameSize;
  QueueFrames		mRecordedData;
  QueueFrames		mPlayData;
  PaError		mErr;
  Babe::NetworkManager* mNetwork;
};

#endif		// ! __AUDIOMANAGERPORTAUDIOIMPL_HPP__

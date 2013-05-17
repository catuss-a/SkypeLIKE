
#ifndef		__PORT_AUDIO_FRAME_HPP__
# define	__PORT_AUDIO_FRAME_HPP__

# include <portaudio.h>
# include <Babe.hpp>
# include <BabeAudioFrame.hpp>

namespace PortAudio
{

  class PortAudioFrame : public Babe::AudioFrame
  {
  public:
    enum {
      SAMPLE_RATE = 8000,
      FRAME_SIZE = 160,
      ENC_FRAME_SIZE = 200,
      CHAN_COUNT = 1,
      SAMPLE_FORMAT = paInt16
    };
    typedef short t_sample;

  public:
    PortAudioFrame() {}
    PortAudioFrame(t_sample *rawFrame, unsigned int frameSize = FRAME_SIZE);
    PortAudioFrame(char const *encFrame, unsigned int frameSize = ENC_FRAME_SIZE);
    PortAudioFrame(PortAudioFrame const&);
    PortAudioFrame& operator=(PortAudioFrame const&);
    virtual ~PortAudioFrame();
    virtual void encode();
    virtual void decode();
    t_sample *getRawData() const;
    char *getEncodedData() const;

  private:
    Babe::CodecManager*		mCodecManager;
    t_sample			mRawFrame[FRAME_SIZE];
    char			mEncFrame[ENC_FRAME_SIZE];
  };

}
#endif		// !__PORT_AUDIO_FRAME_HPP__

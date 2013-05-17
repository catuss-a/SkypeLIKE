
#ifndef		__CODECMANAGERSPEEXIMPL_HPP__
# define	__CODECMANAGERSPEEXIMPL_HPP___

# include <speex/speex.h>
# include <Babe.hpp>

class BABE_DLLREQ CodecManagerSpeexImpl : public Babe::CodecManagerImpl
{
 public:
  CodecManagerSpeexImpl(int quality = 10);
  virtual ~CodecManagerSpeexImpl();
  virtual bool init();
  virtual void shutdown();
  virtual void update(float dt);
  virtual void encode(void * iFrame, void *oFrame);
  virtual void *decode(void * iFrame);

 private:
  int                         mQuality;
  SpeexBits                   mEncBits;
  SpeexBits                   mDecBits;
  void                        *mEncState;
  void                        *mDecState;
  size_t	              mEncFrameSize;
  size_t	              mRawFrameSize;
  int                         mSampleRate;
};

#endif		// ! __CODECMANAGERSPEEXIMPL_HPP___

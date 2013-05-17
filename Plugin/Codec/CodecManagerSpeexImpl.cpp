
#include "CodecManagerSpeexImpl.hpp"

CodecManagerSpeexImpl::CodecManagerSpeexImpl(int quality) :
  mQuality(quality >= 0 && quality <= 10 ? quality:5),
  mEncFrameSize(Babe::AudioManager::getSingletonPtr()->getAudioEncFrameSize()),
  mRawFrameSize(Babe::AudioManager::getSingletonPtr()->getAudioRawFrameSize())
{
  speex_bits_init(&mEncBits);
  mEncState = speex_encoder_init(&speex_nb_mode);
  speex_encoder_ctl(mEncState, SPEEX_SET_QUALITY, &mQuality);
  speex_bits_init(&mDecBits);
  mDecState = speex_decoder_init(&speex_nb_mode);
}

CodecManagerSpeexImpl::~CodecManagerSpeexImpl()
{
  speex_encoder_destroy(mEncState);
  speex_bits_destroy(&mEncBits);
  speex_decoder_destroy(mDecState);
  speex_bits_destroy(&mDecBits);
}

bool CodecManagerSpeexImpl::init()
{
  Babe::LOG("CodecManagerSpeexImpl initialized");
  return true;
}

void CodecManagerSpeexImpl::shutdown()
{
}

void CodecManagerSpeexImpl::update(float)
{
}

void CodecManagerSpeexImpl::encode(void * iFrame, void *oFrame)
{
  float input[160];
  short *inputFrame = static_cast<short*>(iFrame);

  for (int i = 0; i < 160; ++i)
    input[i] = static_cast<float>(inputFrame[i]);
  speex_bits_reset(&mEncBits);
  speex_encode(mEncState, input, &mEncBits);
  speex_bits_write(&mEncBits, static_cast<char*>(oFrame), 200);
}

void *CodecManagerSpeexImpl::decode(void * iFrame)
{
  char * rIFrame = static_cast<char *>(iFrame);
  short* finalData = new short[mRawFrameSize];
  float buff[mRawFrameSize];

  for (unsigned int i = 0 ; i < mRawFrameSize; ++i)
    buff[i] = 0;
  speex_bits_read_from(&mDecBits, rIFrame, mEncFrameSize);
  speex_decode(mDecState, &mDecBits, buff);
  for (unsigned int i = 0; i < mRawFrameSize; ++i)
    finalData[i] = static_cast<short>(buff[i]);
  return finalData;
}

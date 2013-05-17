
#include "PortAudioFrame.hpp"

namespace PortAudio
{

  PortAudioFrame::PortAudioFrame(t_sample *rawFrame, unsigned int frameSize)
  {
    unsigned int i = frameSize > static_cast<int>(FRAME_SIZE) ? static_cast<int>(FRAME_SIZE) : frameSize;
    for (unsigned int j = 0; j < i; ++j)
      mRawFrame[j] = rawFrame[j];
    mState = RAW;
    mCodecManager = Babe::CodecManager::getSingletonPtr();
  }

  PortAudioFrame::PortAudioFrame(char const *encFrame, unsigned int frameSize)
  {
    for (unsigned int j = 0; j < frameSize; ++j) {
      mEncFrame[j] = encFrame[j];
    }
    mState = ENCODED;
    mCodecManager = Babe::CodecManager::getSingletonPtr();
  }

  PortAudioFrame::PortAudioFrame(PortAudioFrame const&oth) :
    Babe::AudioFrame()
  {
    this->mState = oth.mState;
    this->mCodecManager = oth.mCodecManager;
    for (int i = 0; i < FRAME_SIZE; ++i)
      this->mRawFrame[i] = oth.mRawFrame[i];
    for (int i = 0; i < ENC_FRAME_SIZE; ++i)
      this->mEncFrame[i] = oth.mEncFrame[i];
  }

  PortAudioFrame& PortAudioFrame::operator=(PortAudioFrame const& oth)
  {
    if (this != &oth)
      {
	this->mState = oth.mState;
	this->mCodecManager = oth.mCodecManager;
	for (int i = 0; i < FRAME_SIZE; ++i)
	  this->mRawFrame[i] = oth.mRawFrame[i];
	for (int i = 0; i < ENC_FRAME_SIZE; ++i)
	  this->mEncFrame[i] = oth.mEncFrame[i];
      }
    return *this;
  }

  PortAudioFrame::~PortAudioFrame()
  {
  }

  void PortAudioFrame::encode()
  {
    if (mState == RAW) {
      mCodecManager->encode(mRawFrame, mEncFrame);
      mState = ENCODED;
    }
  }

  void PortAudioFrame::decode()
  {
    if (mState == ENCODED) {
      short *data = static_cast<short*>(mCodecManager->decode(mEncFrame));
      for (int i = 0; i < FRAME_SIZE; ++i)
	mRawFrame[i] = data[i];
      mState = RAW;
    }
  }

  PortAudioFrame::t_sample *PortAudioFrame::getRawData() const
  {
    PortAudioFrame::t_sample *data =
      new PortAudioFrame::t_sample[FRAME_SIZE];

    for (int i = 0; i < FRAME_SIZE; ++i)
      data[i] = mRawFrame[i];
    return data;
  }

  char* PortAudioFrame::getEncodedData() const
  {
    char *encData = new char[ENC_FRAME_SIZE];

    for (int i = 0; i < ENC_FRAME_SIZE; ++i)
      encData[i] = mEncFrame[i];
    return encData;
  }
}

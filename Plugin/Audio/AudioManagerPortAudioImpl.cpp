
#include <string>
#include "AudioManagerPortAudioImpl.hpp"

AudioManagerPortAudioImpl::AudioManagerPortAudioImpl(int sampleRate,
						     int frameSize) :
  mIsOn(false),
  mOStream(NULL),
  mIStream(NULL),
  mSampleRate(sampleRate),
  mFrameSize(frameSize),
  mErr(paNoError)
{
  Babe::AudioManager::getSingletonPtr()->setAudioEncFrameSize(PortAudio::PortAudioFrame::ENC_FRAME_SIZE);
  Babe::AudioManager::getSingletonPtr()->setAudioRawFrameSize(PortAudio::PortAudioFrame::FRAME_SIZE);
  if ((mErr = Pa_Initialize()) != paNoError) {
    Babe::LOGE("Error: Pa_Initialize");
    return ;
  }
  if (!this->OpenStream(INPUT))
    return ;
  if (!this->OpenStream(OUTPUT))
    return ;
}

AudioManagerPortAudioImpl::~AudioManagerPortAudioImpl()
{
  if ((mErr = Pa_CloseStream(mOStream)) != paNoError
      || (mErr = Pa_CloseStream(mIStream)) != paNoError)
    Babe::LOGE("Error: Pa_CloseStream");
  if ((mErr = Pa_Terminate()) != paNoError)
    Babe::LOGE("Error: Pa_Terminate");
}

bool AudioManagerPortAudioImpl::init()
{
  Babe::LOG("AudioManagerPortAudioImpl initialized");
  mNetwork = Babe::NetworkManager::getSingletonPtr();
  return true;
}

void AudioManagerPortAudioImpl::shutdown()
{
  while (!mRecordedData.empty()) {
    mRecordedData.pop();
  }
  while (!mPlayData.empty()) {
    mPlayData.pop();
  }
}

void AudioManagerPortAudioImpl::update(float)
{
  if (mIsOn)
    {
      PortAudio::PortAudioFrame* frameToSend = 0;
      Babe::AudioFrame* getFrontFrame = recordAudioFrame();

      if (getFrontFrame)
	frameToSend = static_cast<PortAudio::PortAudioFrame*>(getFrontFrame);
      if (frameToSend)
	{
	  frameToSend->encode();
	  char* data = frameToSend->getEncodedData();
	  mNetwork->sendData(PortAudio::PortAudioFrame::ENC_FRAME_SIZE, data);
	  delete data;
	  delete frameToSend;
	}
    }
}

void AudioManagerPortAudioImpl::on()
{
  if (!mIsOn) {
    if ((mErr = Pa_StartStream(mIStream)) != paNoError) {
      Babe::LOGE("Error: Pa_StartStreamIstream");
      return ;
    }
    if ((mErr = Pa_StartStream(mOStream)) != paNoError) {
      Babe::LOGE("Error: Pa_StartStreamOstream");
      return ;
    }
    mIsOn = true;
  }
}

void AudioManagerPortAudioImpl::off()
{
  if (mIsOn) {
    if ((mErr = Pa_StopStream(mIStream)) != paNoError) {
      Babe::LOGE("Error: Pa_StopStream");
      return ;
    }
    if ((mErr = Pa_StopStream(mOStream)) != paNoError) {
      Babe::LOGE("Error: Pa_StopStream");
      return ;
    }
    mIsOn = false;
  }
}

Babe::AudioFrame* AudioManagerPortAudioImpl::recordAudioFrame()
{
  PortAudio::PortAudioFrame *ret = 0;
  PortAudio::PortAudioFrame *frame = 0;

  if (!mRecordedData.empty()) {
    frame = mRecordedData.front();
    ret = new PortAudio::PortAudioFrame(*frame);
    mRecordedData.pop();
  }
  return ret;
}

// deprecated
void AudioManagerPortAudioImpl::playAudioFrame(Babe::AudioFrame* frame)
{
  PortAudio::PortAudioFrame *f;

  f = static_cast<PortAudio::PortAudioFrame*>(frame);
  if (f) {
    if (f->getState() == Babe::AudioFrame::ENCODED)
      f->decode();
    mPlayData.push(f);
  }
}

void AudioManagerPortAudioImpl::playAudioFrame(char const* cframe,
					       size_t frameSize)
{
  PortAudio::PortAudioFrame *f =
    new PortAudio::PortAudioFrame(cframe, frameSize);

  if (f) {
    f->decode();
    mPlayData.push(f);
  }
}

bool AudioManagerPortAudioImpl::OpenStream(eAudioType type)
{
  if (type == INPUT) {
    if (!this->SetParameters(&mIParameters, Pa_GetDefaultInputDevice()))
      return false;
    mIParameters.suggestedLatency =
      Pa_GetDeviceInfo(mIParameters.device)->defaultLowInputLatency;
  } else if (type == OUTPUT) {
    if (!this->SetParameters(&mOParameters, Pa_GetDefaultOutputDevice()))
      return false;
    this->mOParameters.suggestedLatency =
      Pa_GetDeviceInfo(mOParameters.device)->defaultLowOutputLatency;
  } else return false;
  if ((mErr = Pa_OpenStream(type == INPUT ? &mIStream:&mOStream,
			    type == INPUT ? &mIParameters:0,
			    type == OUTPUT ? &mOParameters:0,
			    mSampleRate,
			    mFrameSize,
			    paClipOff,
			    &AudioManagerPortAudioImpl::CallBack,
			    this)) != paNoError) {
    Babe::LOGE("Error: Pa_OpenStream");
    return false;
  }
  return true;
}

bool AudioManagerPortAudioImpl::SetParameters(PaStreamParameters *params,
					      PaDeviceIndex inputDevice,
					      int chanCount,
					      PaSampleFormat spFormat,
					      void *hostAPI)
{
  if ((mErr = inputDevice) == paNoDevice) {
    Babe::LOGE("Error: Pa_getDefaultDevice");
    return false;
  }
  params->device = inputDevice;
  params->channelCount = chanCount;
  params->sampleFormat = spFormat;
  params->hostApiSpecificStreamInfo = hostAPI;
  return true;
}

int AudioManagerPortAudioImpl::CallBack(const void *input, void *output,
					unsigned long frameCount,
					const PaStreamCallbackTimeInfo* timeInfo,
					PaStreamCallbackFlags statusFlags,
					void *userData)
{
  AudioManagerPortAudioImpl *ptrThis;

  ptrThis = static_cast<AudioManagerPortAudioImpl*>(userData);
  if (input)
    {
      return  (ptrThis->StartRecord(input, output,
				    frameCount, timeInfo,
				    statusFlags));
    }
  else if (output) {
    return (ptrThis->StartVoice(input, output,
				frameCount, timeInfo,
				statusFlags));
  }
  return 0;
}

int AudioManagerPortAudioImpl::StartVoice(const void *, void *output,
					  unsigned long frameCount,
					  const PaStreamCallbackTimeInfo*,
					  PaStreamCallbackFlags)
{
  PortAudio::PortAudioFrame::t_sample *wonOutPut =
    static_cast<PortAudio::PortAudioFrame::t_sample*>(output);
  PortAudio::PortAudioFrame::t_sample *data;
  PortAudio::PortAudioFrame *frame;

  for (unsigned int i = 0; i < frameCount; ++i)
    wonOutPut[i] = 0;
  if (output)
    {
      if (!mPlayData.empty()) {
	frame = mPlayData.front();
  	data = frame->getRawData();
  	for (unsigned int i = 0; i < frameCount; ++i)
  	  wonOutPut[i] = data[i];
  	mPlayData.pop();
  	delete data;
      }
      return paContinue;
    }
  return paComplete;
}

int AudioManagerPortAudioImpl::StartRecord(const void *input, void *output,
					   unsigned long frameCount,
					   const PaStreamCallbackTimeInfo*timeInfo,
					   PaStreamCallbackFlags flags)
{
  PortAudio::PortAudioFrame::t_sample const* ronInput
    = static_cast<PortAudio::PortAudioFrame::t_sample const*>(input);
  PortAudio::PortAudioFrame::t_sample* recordedSound =
    new PortAudio::PortAudioFrame::t_sample[frameCount];

  (void)output;(void)timeInfo;(void)flags;
  for (unsigned int i = 0; i < frameCount; ++i)
    recordedSound[i] = 0;
  if (input)
    {
      for (unsigned int i = 0; i < frameCount; ++i)
  	recordedSound[i] = ronInput[i];
      PortAudio::PortAudioFrame *nFrame =
	new PortAudio::PortAudioFrame(recordedSound);
      mRecordedData.push(nFrame);
      delete recordedSound;
      return paContinue;
    }
  return paComplete;
}

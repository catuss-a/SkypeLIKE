
#include "BabeCodecManager.hpp"
#include "BabeLogManager.hpp"

namespace Babe
{
  CodecManager* CodecManager::getSingletonPtr()
  {
    return msSingleton;
  }

  CodecManager& CodecManager::getSingleton()
  {
    ASSERT_SINGLETON( msSingleton, "CodecManager", "getSingleton()" );  return ( *msSingleton );  
  }

  CodecManager::CodecManager()
    : System("CodecSystem")
  {
    mImpl = &mDummyImpl;
    LOG("CodecManager created");
  }

  CodecManager::~CodecManager()
  {
  }

  bool CodecManager::init()
  {
    return mImpl->init();
  }

  void CodecManager::shutdown()
  {
    mImpl->shutdown();
  }

  void CodecManager::update(float dt)
  {
    mImpl->update(dt);
  }

  void CodecManager::setImpl(SystemImpl* impl)
  {
    if (impl)
      {
	if (!(mImpl = dynamic_cast<CodecManagerImpl*>(impl)))
	  {
	    LOGE("CodecManager::setImpl the implementation is not a CodecManagerImpl*");
	    mImpl = &mDummyImpl;
	  }
      }
  }

  void CodecManager::unsetImpl()
  {
    mImpl = &mDummyImpl;
  }

  void CodecManager::encode(void * iFrame, void *oFrame)
  {
    mImpl->encode(iFrame, oFrame);
  }

  void *CodecManager::decode(void * iFrame)
  {
    return mImpl->decode(iFrame);
  }


} // End of namespace Babe

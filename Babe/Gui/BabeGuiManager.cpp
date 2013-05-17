//
// BabeGuiManager.cpp for  in /home/allaux_c/babel-2014-champi_d/Babe/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sun Nov 20 14:38:30 2011 Chanh Allaux
// Last update Wed Nov 30 18:30:30 2011 Chanh Allaux
//

#include "BabeGuiManager.hpp"
#include "BabeLogManager.hpp"

namespace Babe
{
	GuiManager* GuiManager::getSingletonPtr()
	{
		return msSingleton;
	}

	GuiManager& GuiManager::getSingleton()
	{
        ASSERT_SINGLETON( msSingleton, "GuiManager", "getSingleton()" );  return ( *msSingleton );  
	}

  GuiManager::GuiManager()
    : System("GuiSystem")
  {
    mImpl = &mDummyImpl;
    LOG("GuiManager created");
  }

  GuiManager::~GuiManager()
  {
  }

  bool GuiManager::init()
  {
    return mImpl->init();
  }

  void GuiManager::shutdown()
  {
    mImpl->shutdown();
  }

  void GuiManager::update(float dt)
  {
    mImpl->update(dt);
  }

  void GuiManager::notify(std::string const& notification)
  {
    mImpl->notify(notification);
  }

  void GuiManager::setImpl(SystemImpl* impl)
  {
    if (impl)
      {
	if (!(mImpl = dynamic_cast<GuiManagerImpl*>(impl)))
	  {
	    LOGE("GuiManager::setImpl the implementation is not a GuiManagerImpl*");
	    mImpl = &mDummyImpl;
	  }
      }
  }

  void GuiManager::unsetImpl()
  {
    mImpl = &mDummyImpl;
  }

} // End of namespace Babe

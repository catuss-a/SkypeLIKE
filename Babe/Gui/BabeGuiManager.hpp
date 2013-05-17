//
// BabeGuiManager.hpp for  in /home/allaux_c/babel-2014-champi_d/Babe/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sun Nov 20 14:37:59 2011 Chanh Allaux
// Last update Wed Nov 30 17:31:40 2011 alexandre champion
//

#ifndef		__BABE_GUIMANAGER_HPP__
# define	__BABE_GUIMANAGER_HPP__

# include <string>
# include "BabeDef.hpp"
# include "BabeSingleton.hpp"
# include "BabeSystem.hpp"
# include "BabeGuiManagerImpl.hpp"

namespace Babe
{

  class BABE_DLLREQ GuiManager : public Singleton<GuiManager>, public System
  {
  public:
    GuiManager();
    virtual ~GuiManager();
    virtual bool init();
    virtual void shutdown();
    virtual void update(float dt);
    void notify(std::string const& notification);
    virtual void setImpl(SystemImpl* impl);
    virtual void unsetImpl();
	static GuiManager* getSingletonPtr();
	static GuiManager& getSingleton();

  private:
    GuiManagerDummyImpl	mDummyImpl;
    GuiManagerImpl*		mImpl;
  };

} // End of namespace Babe

#endif		// ! __BABE_GUIMANAGER_HPP__

//
// BabeGuiManagerImpl.hpp for  in /home/allaux_c/babel-2014-champi_d/Babe/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sun Nov 20 14:39:19 2011 Chanh Allaux
// Last update Sun Dec  4 18:43:11 2011 alexandre champion
//

#ifndef		__BABE_GUIMANAGERIMPL_HPP__
# define	__BABE_GUIMANAGERIMPL_HPP__

# include <string>
# include "BabeDef.hpp"
# include "BabeSystemImpl.hpp"
# include "BabeLogManager.hpp"

namespace Babe
{

  class BABE_DLLREQ GuiManagerImpl : public SystemImpl
  {
  public:
    virtual ~GuiManagerImpl() {}
    virtual bool init() = 0;
    virtual void shutdown() = 0;
    virtual void update(float dt) = 0;
    virtual void notify(std::string const& notification) = 0;
  };

  class BABE_DLLREQ GuiManagerDummyImpl : public GuiManagerImpl
  {
  public:
    GuiManagerDummyImpl() : mFirstUpdate(false) {}
    virtual ~GuiManagerDummyImpl() {}
    virtual bool init() { LOG("GuiManagerDummyImpl initialized"); return true; }
    virtual void shutdown() {}
    virtual void update(float);
    virtual void notify(std::string const& notification) { LOG("GuiManagerDummyImpl notify(\"" + notification + "\")"); }

  private:
    bool mFirstUpdate;
  };

} // End of namespace Babe

#endif		// ! __BABE_GUIMANAGERIMPL_HPP__

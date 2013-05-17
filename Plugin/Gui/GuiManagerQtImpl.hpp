//
// GuiManagerQtImpl.hpp for  in /home/allaux_c/babel-2014-champi_d/Plugin/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sun Nov 20 14:12:54 2011 Chanh Allaux
// Last update Sun Dec  4 21:22:28 2011 alexandre champion
//

#ifndef		__GUIMANAGERQTIMPL_HPP__
# define	__GUIMANAGERQTIMPL_HPP__

# include <Babe.hpp>
# include "QSingletonApplication.hpp"
# include "BabelLoginWindow.hpp"
# include "BabelNotifications.hpp"

class BABE_DLLREQ GuiManagerQtImpl : public Babe::GuiManagerImpl
{
public:
  GuiManagerQtImpl();
  virtual ~GuiManagerQtImpl();
  virtual bool init();
  virtual void shutdown();
  virtual void update(float dt);
  virtual void notify(const std::string&);

private:
  int argc;
  char** argv;
  QSingletonApplication* mApp;
  BabelLoginWindow* mWindow;
  BabelNotifications* mNotifications;
  bool mFirstInit;
};

#endif		// ! __GUIMANAGERQTIMPL_HPP__

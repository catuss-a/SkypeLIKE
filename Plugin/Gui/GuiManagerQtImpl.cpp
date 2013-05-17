//
// GuiManagerQtImpl.cpp for  in /home/allaux_c/babel-2014-champi_d/Plugin/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sun Nov 20 14:11:46 2011 Chanh Allaux
// Last update Sun Dec  4 21:46:45 2011 alexandre champion
//

#include <QSplashScreen>
#include <QPixmap>
#include <QDesktopWidget>
#include "GuiManagerQtImpl.hpp"
#include "BabelMainWindow.hpp"

#include <cerrno>

GuiManagerQtImpl::GuiManagerQtImpl()
    : argc(0), argv(0),
      mNotifications(new BabelNotifications),
      mFirstInit(true)
{
}

GuiManagerQtImpl::~GuiManagerQtImpl()
{
}

bool GuiManagerQtImpl::init()
{
  Babe::LOG("GuiManagerQtImpl initialized");
  if (mFirstInit)
    {
      mApp = new QSingletonApplication(argc, argv);
      mFirstInit = false;
    }
  mApp->loginWindow = new BabelLoginWindow();
  mApp->loginWindow->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, mApp->loginWindow->size(), mApp->desktop()->availableGeometry()));
  QPixmap labgay(":/images/background/Resources/labgay.png");
  QSplashScreen splash(labgay);
  splash.show();
  mApp->processEvents();
  mApp->loginWindow->show();
  splash.finish(mApp->loginWindow);
  return true;
}

void GuiManagerQtImpl::shutdown()
{
  Babe::CommandManager::getSingletonPtr()->execute("updateuserstatus disconnected");
  delete mApp->loginWindow;
  delete mApp->mainWindow;
  mApp->loginWindow = 0;
  mApp->mainWindow = 0;
}

void GuiManagerQtImpl::update(float)
{
   mApp->processEvents();
}

void GuiManagerQtImpl::notify(const std::string& cmd)
{
	mNotifications->notify(cmd);
}

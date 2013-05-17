//
// GuiPluginQt.cpp for  in /home/allaux_c/babel-2014-champi_d/Plugin/Gui
//
// Made by Chanh Allaux
// Login   <allaux_c@epitech.net>
//
// Started on  Sun Nov 20 14:14:33 2011 Chanh Allaux
// Last update Mon Nov 21 19:37:32 2011 Chanh Allaux
//

#include <Babe.hpp>
#include "GuiManagerQtImpl.hpp"

typedef Babe::PluginTpl<GuiManagerQtImpl> GuiPluginQt;

extern "C"
{
  BABE_DLLREQ bool registerPlugin(Babe::PluginManagerImpl* pluginManager, void* dlHandle)
  {
    Babe::PluginManagerImpl::PluginParams pp;
    pp.dlHandle = dlHandle;
    pp.createFct = &GuiPluginQt::createInstance;
    pp.destroyFct = &GuiPluginQt::destroyInstance;
    pp.systemName = "GuiSystem";
    pp.pluginName = "GuiPluginQt";
    pp.version = "0.0";
    if (!pluginManager->registerPlugin(&pp))
      return false;
    return true;
  }
}

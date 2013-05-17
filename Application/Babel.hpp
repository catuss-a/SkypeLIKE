//
// Babe.hpp for  in /home/champi_d//AdvancedCPP/Babel
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Tue Nov 15 16:46:18 2011 alexandre champion
// Last update Sun Dec  4 18:06:53 2011 alexandre champion
//

#ifndef		__BABEL_HPP__
# define	__BABEL_HPP__

#include <Babe.hpp>

class Babel
{
public:
  Babel();
  ~Babel();
  void run();

private:
  void registerCommands();
  void registerConnectionManagementCmds();
  void registerUserStatusManagementCmds();
  void registerContactManagementCmds();
  void registerCallManagementCmds();
  void registerErrorManagementCmds();
  void registerTextManagementCmds();

private:
  Babe::ApplicationManager*	mApp;
  Babe::CommandManager*		mCmdMgr;
};

#endif		// ! __BABEL_HPP__

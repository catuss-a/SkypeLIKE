//
// BabeLoadPluginCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d/Babe
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Mon Nov 28 17:26:39 2011 alexandre champion
// Last update Mon Nov 28 18:24:49 2011 alexandre champion
//

#ifndef		__BABE_LOADPLUGINCMD_HPP__
# define	__BABE_LOADPLUGINCMD_HPP__

# include <string>
# include "BabeICommand.hpp"

namespace Babe
{

  class BABE_DLLREQ LoadPluginCmd : public ICommand
  {
  public:
    LoadPluginCmd(std::string const& pluginPath);
    LoadPluginCmd(CommandParser::ArgVector& args);
    virtual void exec();
    virtual std::string const& getName() const;
    virtual std::string const& stringify();

  private:
	std::string mName;
    std::string mPluginPath;
    std::string mStringified;
  };

} // End of namespace Babe

#endif		// ! __BABE_LOADPLUGINCMD_HPP__

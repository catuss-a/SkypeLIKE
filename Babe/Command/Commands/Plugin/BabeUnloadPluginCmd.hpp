//
// BabeUnloadPluginCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Dec  4 13:09:16 2011 alexandre champion
// Last update Sun Dec  4 13:11:27 2011 alexandre champion
//

#ifndef		__BABE_UNLOADPLUGINCMD_HPP__
# define	__BABE_UNLOADPLUGINCMD_HPP__

# include <string>
# include "BabeICommand.hpp"

namespace Babe
{

  class BABE_DLLREQ UnloadPluginCmd : public ICommand
  {
  public:
    UnloadPluginCmd(std::string const& pluginPath);
    UnloadPluginCmd(CommandParser::ArgVector& args);
    virtual void exec();
    virtual std::string const& getName() const;
    virtual std::string const& stringify();

  private:
    std::string mName;
    std::string mPluginPath;
    std::string mStringified;
  };

} // End of namespace Babe

#endif		// ! __BABE_UNLOADPLUGINCMD_HPP__

//
// BabeQuitCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Babe
//
// Made by alexandre champion
// Login   <champi_d@epitech.net>
//
// Started on  Sun Nov 13 20:54:05 2011 alexandre champion
// Last update Mon Nov 28 18:18:10 2011 alexandre champion
//

#ifndef		__BABE_QUITCMD_HPP__
# define	__BABE_QUITCMD_HPP__

# include "BabeICommand.hpp"

namespace Babe
{

  class BABE_DLLREQ QuitCmd : public ICommand
  {
  public:
    QuitCmd();
    QuitCmd(CommandParser::ArgVector&);
    virtual void exec();
    virtual std::string const& getName() const;

  private:
	  std::string mName;
  };

} // End of namespace Babe

#endif		// ! __BABE_QUITCMD_HPP__

//
// BabeUndo.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Fri Dec  2 18:10:54 2011 alexandre champion
// Last update Fri Dec  2 18:18:06 2011 alexandre champion
//

#ifndef		__BABE_UNDOCMD_HPP__
# define	__BABE_UNDOCMD_HPP__

# include "BabeICommand.hpp"

namespace Babe
{

  class BABE_DLLREQ UndoCmd : public ICommand
  {
  public:
    UndoCmd();
    UndoCmd(CommandParser::ArgVector&);
    virtual ~UndoCmd();
    virtual void exec();
    virtual std::string const& getName() const;

  private:
	  std::string mName;
  };

} // End of namespace Babe

#endif		// ! __BABE_UNDOCMD_HPP__

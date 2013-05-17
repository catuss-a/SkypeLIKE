//
// SuspendCallCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Fri Dec  2 16:42:07 2011 alexandre champion
// Last update Fri Dec  2 16:43:01 2011 alexandre champion
//

#ifndef		__SUSPENDCALLCMD_HPP__
# define	__SUSPENDCALLCMD_HPP__

# include <string>
# include <Babe.hpp>

class SuspendCallCmd : public Babe::ICommand
{
public:
  SuspendCallCmd(std::string const& login);
  SuspendCallCmd(Babe::CommandParser::ArgVector& args);
  virtual ~SuspendCallCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mStringified;
};

#endif		// ! __SUSPENDCALLCMD_HPP__

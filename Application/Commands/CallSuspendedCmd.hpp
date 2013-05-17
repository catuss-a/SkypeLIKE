//
// CallSuspendedCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Fri Dec  2 16:48:24 2011 alexandre champion
// Last update Fri Dec  2 16:49:53 2011 alexandre champion
//

#ifndef		__CALLSUSPENDEDCMD_HPP__
# define	__CALLSUSPENDEDCMD_HPP__

# include <string>
# include <Babe.hpp>

class CallSuspendedCmd : public Babe::ICommand
{
public:
  CallSuspendedCmd(std::string const& login);
  CallSuspendedCmd(Babe::CommandParser::ArgVector& args);
  virtual ~CallSuspendedCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mStringified;
};

#endif		// ! __CALLSUSPENDEDCMD_HPP__

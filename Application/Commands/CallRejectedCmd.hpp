//
// CallRejectedCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 23:57:05 2011 alexandre champion
// Last update Thu Dec  1 23:57:23 2011 alexandre champion
//

#ifndef		__CALLREJECTEDCMD_HPP__
# define	__CALLREJECTEDCMD_HPP__

# include <string>
# include <Babe.hpp>

class CallRejectedCmd : public Babe::ICommand
{
public:
  CallRejectedCmd(std::string const& login);
  CallRejectedCmd(Babe::CommandParser::ArgVector& args);
  virtual ~CallRejectedCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mStringified;
};

#endif		// ! __CALLREJECTEDCMD_HPP__

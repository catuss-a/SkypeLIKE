//
// CallAcceptedCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 23:49:52 2011 alexandre champion
// Last update Thu Dec  1 23:50:23 2011 alexandre champion
//

#ifndef		__CALLACCEPTEDCMD_HPP__
# define	__CALLACCEPTEDCMD_HPP__

# include <string>
# include <Babe.hpp>

class CallAcceptedCmd : public Babe::ICommand
{
public:
  CallAcceptedCmd(std::string const& login);
  CallAcceptedCmd(Babe::CommandParser::ArgVector& args);
  virtual ~CallAcceptedCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mStringified;
};

#endif		// ! __CALLACCEPTEDCMD_HPP__

//
// AcceptContactRequestCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 22:37:01 2011 alexandre champion
// Last update Thu Dec  1 22:37:44 2011 alexandre champion
//

#ifndef		__ACCEPTCONTACTREQUESTCMD_HPP__
# define	__ACCEPTCONTACTREQUESTCMD_HPP__

# include <string>
# include <Babe.hpp>

class AcceptContactRequestCmd : public Babe::ICommand
{
public:
  AcceptContactRequestCmd(std::string const& login);
  AcceptContactRequestCmd(Babe::CommandParser::ArgVector& args);
  virtual ~AcceptContactRequestCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mStringified;
};

#endif		// ! __ACCEPTCONTACTREQUESTCMD_HPP__

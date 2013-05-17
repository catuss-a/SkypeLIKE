//
// AcceptCallCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 23:46:11 2011 alexandre champion
// Last update Thu Dec  1 23:47:23 2011 alexandre champion
//

#ifndef		__ACCEPTCALLCMD_HPP__
# define	__ACCEPTCALLCMD_HPP__

# include <string>
# include <Babe.hpp>

class AcceptCallCmd : public Babe::ICommand
{
public:
  AcceptCallCmd(std::string const& login);
  AcceptCallCmd(Babe::CommandParser::ArgVector& args);
  virtual ~AcceptCallCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mStringified;
};

#endif		// ! __ACCEPTCALLCMD_HPP__

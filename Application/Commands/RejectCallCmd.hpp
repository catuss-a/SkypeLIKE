//
// RejectCallCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 23:53:38 2011 alexandre champion
// Last update Thu Dec  1 23:54:04 2011 alexandre champion
//

#ifndef		__REJECTCALLCMD_HPP__
# define	__REJECTCALLCMD_HPP__

# include <string>
# include <Babe.hpp>

class RejectCallCmd : public Babe::ICommand
{
public:
  RejectCallCmd(std::string const& login);
  RejectCallCmd(Babe::CommandParser::ArgVector& args);
  virtual ~RejectCallCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mStringified;
};

#endif		// ! __REJECTCALLCMD_HPP__

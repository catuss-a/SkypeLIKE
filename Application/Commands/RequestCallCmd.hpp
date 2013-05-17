//
// RequestCallCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 23:36:51 2011 alexandre champion
// Last update Thu Dec  1 23:37:49 2011 alexandre champion
//

#ifndef		__REQUESTCALLCMD_HPP__
# define	__REQUESTCALLCMD_HPP__

# include <string>
# include <Babe.hpp>

class RequestCallCmd : public Babe::ICommand
{
public:
  RequestCallCmd(std::string const& login);
  RequestCallCmd(Babe::CommandParser::ArgVector& args);
  virtual ~RequestCallCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mStringified;
};

#endif		// ! __REQUESTCALLCMD_HPP__

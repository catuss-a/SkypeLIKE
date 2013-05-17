//
// UserConnectCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Wed Nov 30 18:01:56 2011 alexandre champion
// Last update Thu Dec  1 14:39:24 2011 alexandre champion
//

#ifndef		__USERCONNECTCMD_HPP__
# define	__USERCONNECTCMD_HPP__

# include <string>
# include <Babe.hpp>

class UserConnectCmd : public Babe::ICommand
{
public:
  UserConnectCmd(std::string const& userName, std::string const& userPassword);
  UserConnectCmd(Babe::CommandParser::ArgVector& args);
  virtual ~UserConnectCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mUserName;
  std::string mUserPassword;
  std::string mStringified;
};

#endif		// ! __USERCONNECTCMD_HPP__

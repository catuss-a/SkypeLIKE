//
// UserStatusCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 22:02:51 2011 alexandre champion
// Last update Thu Dec  1 22:04:29 2011 alexandre champion
//

#ifndef		__USERSTATUSCMD_HPP__
# define	__USERSTATUSCMD_HPP__

# include <string>
# include <Babe.hpp>

class UserStatusCmd : public Babe::ICommand
{
public:
  UserStatusCmd(std::string const& login, std::string const& status);
  UserStatusCmd(Babe::CommandParser::ArgVector& args);
  virtual ~UserStatusCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mStatus;
  std::string mStringified;
};

#endif		// ! __USERSTATUSCMD_HPP__

//
// UserConnectionFailedCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 14:01:32 2011 alexandre champion
// Last update Thu Dec  1 14:26:06 2011 alexandre champion
//

#ifndef		__USERCONNECTIONFAILEDCMD_HPP__
# define	__USERCONNECTIONFAILEDCMD_HPP__

# include <string>
# include <Babe.hpp>

/*
** Command executed from the network to tell the gui the
** connection failed
*/
class UserConnectionFailedCmd : public Babe::ICommand
{
public:
  UserConnectionFailedCmd(std::string const& errorMessage);
  UserConnectionFailedCmd(Babe::CommandParser::ArgVector& args);
  virtual ~UserConnectionFailedCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mErrorMessage;
  std::string mStringified;
};

#endif		// ! __USERCONNECTIONFAILEDCMD_HPP__

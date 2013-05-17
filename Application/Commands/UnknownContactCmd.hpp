//
// UnknownContactCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d/Application/Commands
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Dec  4 00:27:55 2011 alexandre champion
// Last update Sun Dec  4 00:32:39 2011 alexandre champion
//

#ifndef		__UNKWONWCONTACTCMD_HPP__
# define	__UNKWOWNCONTACTCMD_HPP__

# include <string>
# include <Babe.hpp>

class UnknownContactCmd : public Babe::ICommand
{
public:
  UnknownContactCmd(std::string const& login);
  UnknownContactCmd(Babe::CommandParser::ArgVector& args);
  virtual ~UnknownContactCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mStringified;
};

#endif		// ! __ADDCONTACTCMD_HPP__

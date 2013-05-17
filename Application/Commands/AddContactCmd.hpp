//
// AddContactCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 22:26:58 2011 alexandre champion
// Last update Thu Dec  1 22:27:57 2011 alexandre champion
//

#ifndef		__ADDCONTACTCMD_HPP__
# define	__ADDCONTACTCMD_HPP__

# include <string>
# include <Babe.hpp>

class AddContactCmd : public Babe::ICommand
{
public:
  AddContactCmd(std::string const& login);
  AddContactCmd(Babe::CommandParser::ArgVector& args);
  virtual ~AddContactCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mStringified;
};

#endif		// ! __ADDCONTACTCMD_HPP__

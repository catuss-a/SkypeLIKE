//
// ContactRequestCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 22:31:04 2011 alexandre champion
// Last update Thu Dec  1 22:32:45 2011 alexandre champion
//

#ifndef		__CONTACTREQUESTCMD_HPP__
# define	__CONTACTREQUESTCMD_HPP__

# include <string>
# include <Babe.hpp>

class ContactRequestCmd : public Babe::ICommand
{
public:
  ContactRequestCmd(std::string const& login);
  ContactRequestCmd(Babe::CommandParser::ArgVector& args);
  virtual ~ContactRequestCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mStringified;
};

#endif		// ! __CONTACTREQUESTCMD_HPP__

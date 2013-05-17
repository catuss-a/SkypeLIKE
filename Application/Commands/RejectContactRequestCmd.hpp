//
// RejectContactRequestCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 23:18:43 2011 alexandre champion
// Last update Thu Dec  1 23:19:47 2011 alexandre champion
//

#ifndef		__REJECTCONTACTREQUESTCMD_HPP__
# define	__REJECTCONTACTREQUESTCMD_HPP__

# include <string>
# include <Babe.hpp>

class RejectContactRequestCmd : public Babe::ICommand
{
public:
  RejectContactRequestCmd(std::string const& login);
  RejectContactRequestCmd(Babe::CommandParser::ArgVector& args);
  virtual ~RejectContactRequestCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mStringified;
};

#endif		// ! __REJECTCONTACTREQUESTCMD_HPP__

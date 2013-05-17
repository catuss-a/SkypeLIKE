//
// CallRequestCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 23:41:28 2011 alexandre champion
// Last update Thu Dec  1 23:41:54 2011 alexandre champion
//

#ifndef		__CALLREQUESTCMD_HPP__
# define	__CALLREQUESTCMD_HPP__

# include <string>
# include <Babe.hpp>

class CallRequestCmd : public Babe::ICommand
{
public:
  CallRequestCmd(std::string const& login);
  CallRequestCmd(Babe::CommandParser::ArgVector& args);
  virtual ~CallRequestCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mStringified;
};

#endif		// ! __CALLREQUESTCMD_HPP__

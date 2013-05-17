//
// CallHungUpCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Fri Dec  2 16:36:59 2011 alexandre champion
// Last update Fri Dec  2 16:38:08 2011 alexandre champion
//

#ifndef		__CALLHUNGUPCMD_HPP__
# define	__CALLHUNGUPCMD_HPP__

# include <string>
# include <Babe.hpp>

class CallHungUpCmd : public Babe::ICommand
{
public:
  CallHungUpCmd(std::string const& login);
  CallHungUpCmd(Babe::CommandParser::ArgVector& args);
  virtual ~CallHungUpCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mStringified;
};

#endif		// ! __CALLHUNGUPCMD_HPP__

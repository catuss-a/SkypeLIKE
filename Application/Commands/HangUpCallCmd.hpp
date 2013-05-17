//
// HangUpCallCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Fri Dec  2 00:00:10 2011 alexandre champion
// Last update Fri Dec  2 00:01:08 2011 alexandre champion
//

#ifndef		__HANGUPCALLCMD_HPP__
# define	__HANGUPCALLCMD_HPP__

# include <string>
# include <Babe.hpp>

class HangUpCallCmd : public Babe::ICommand
{
public:
  HangUpCallCmd(std::string const& login);
  HangUpCallCmd(Babe::CommandParser::ArgVector& args);
  virtual ~HangUpCallCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mStringified;
};

#endif		// ! __HANGUPCALLCMD_HPP__

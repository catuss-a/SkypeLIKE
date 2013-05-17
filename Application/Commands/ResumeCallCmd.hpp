//
// ResumeCallCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Fri Dec  2 16:54:24 2011 alexandre champion
// Last update Fri Dec  2 16:54:41 2011 alexandre champion
//

#ifndef		__RESUMECALLCMD_HPP__
# define	__RESUMECALLCMD_HPP__

# include <string>
# include <Babe.hpp>

class ResumeCallCmd : public Babe::ICommand
{
public:
  ResumeCallCmd(std::string const& login);
  ResumeCallCmd(Babe::CommandParser::ArgVector& args);
  virtual ~ResumeCallCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mStringified;
};

#endif		// ! __RESUMECALLCMD_HPP__

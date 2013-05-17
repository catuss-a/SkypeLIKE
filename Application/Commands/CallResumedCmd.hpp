//
// CallResumedCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Fri Dec  2 16:57:16 2011 alexandre champion
// Last update Fri Dec  2 16:57:38 2011 alexandre champion
//

#ifndef		__CALLRESUMEDCMD_HPP__
# define	__CALLRESUMEDCMD_HPP__

# include <string>
# include <Babe.hpp>

class CallResumedCmd : public Babe::ICommand
{
public:
  CallResumedCmd(std::string const& login);
  CallResumedCmd(Babe::CommandParser::ArgVector& args);
  virtual ~CallResumedCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mStringified;
};

#endif		// ! __CALLRESUMEDCMD_HPP__

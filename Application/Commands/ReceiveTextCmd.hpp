//
// ReceiveTextCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Dec  4 18:22:59 2011 alexandre champion
// Last update Sun Dec  4 18:23:30 2011 alexandre champion
//

#ifndef		__RECEIVETEXTCMD_HPP__
# define	__RECEIVETEXTCMD_HPP__

# include <string>
# include <Babe.hpp>

class ReceiveTextCmd : public Babe::ICommand
{
public:
  ReceiveTextCmd(std::string const& login, std::string const& message);
  ReceiveTextCmd(Babe::CommandParser::ArgVector& args);
  virtual ~ReceiveTextCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mMessage;
  std::string mStringified;
};

#endif		// ! __RECEIVETEXTCMD_HPP__

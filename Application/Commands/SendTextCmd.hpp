//
// SendTextCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Dec  4 18:14:27 2011 alexandre champion
// Last update Sun Dec  4 18:23:46 2011 alexandre champion
//

#ifndef		__SENDTEXTCMD_HPP__
# define	__SENDTEXTCMD_HPP__

# include <string>
# include <Babe.hpp>

class SendTextCmd : public Babe::ICommand
{
public:
  SendTextCmd(std::string const& login, std::string const& message);
  SendTextCmd(Babe::CommandParser::ArgVector& args);
  virtual ~SendTextCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mMessage;
  std::string mStringified;
};

#endif		// ! __SENDTEXTCMD_HPP__

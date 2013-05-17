//
// EndCallCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Dec  4 18:08:07 2011 alexandre champion
// Last update Sun Dec  4 18:09:29 2011 alexandre champion
//

#ifndef		__ENDCALLCMD_HPP__
# define	__ENDCALLCMD_HPP__

# include <string>
# include <Babe.hpp>

class EndCallCmd : public Babe::ICommand
{
public:
  EndCallCmd(std::string const& login);
  EndCallCmd(Babe::CommandParser::ArgVector& args);
  virtual ~EndCallCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mStringified;
};

#endif		// ! __ENDCALLCMD_HPP__

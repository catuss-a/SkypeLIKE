//
// ConnectionLostCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Sun Dec  4 18:11:34 2011 alexandre champion
// Last update Sun Dec  4 18:12:12 2011 alexandre champion
//

#ifndef		__CONNECTIONLOSTCMD_HPP__
# define	__CONNECTIONLOSTCMD_HPP__

# include <string>
# include <Babe.hpp>

class ConnectionLostCmd : public Babe::ICommand
{
public:
  ConnectionLostCmd();
  ConnectionLostCmd(Babe::CommandParser::ArgVector& args);
  virtual ~ConnectionLostCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mStringified;
};

#endif		// ! __CONNECTIONLOSTCMD_HPP__

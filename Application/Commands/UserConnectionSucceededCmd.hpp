//
// UserConnectionSucceededCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Wed Nov 30 19:08:22 2011 alexandre champion
// Last update Thu Dec  1 14:43:30 2011 alexandre champion
//

#ifndef		__USERCONNECTIONSUCCEEDEDCMD_HPP__
# define	__USERCONNECTIONSUCCEEDEDCMD_HPP__

# include <string>
# include <Babe.hpp>

class UserConnectionSucceededCmd : public Babe::ICommand
{
public:
  UserConnectionSucceededCmd();
  UserConnectionSucceededCmd(Babe::CommandParser::ArgVector& args);
  virtual ~UserConnectionSucceededCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mStringified;
};

#endif		// ! __USERCONNECTIONSUCCEEDEDCMD_HPP__

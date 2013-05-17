//
// UpdateUserStatusCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 22:11:51 2011 alexandre champion
// Last update Thu Dec  1 22:13:15 2011 alexandre champion
//

#ifndef		__UPDATEUSERSTATUSCMD_HPP__
# define	__UPDATEUSERSTATUSCMD_HPP__

# include <string>
# include <Babe.hpp>

class UpdateUserStatusCmd : public Babe::ICommand
{
public:
  UpdateUserStatusCmd(std::string const& status);
  UpdateUserStatusCmd(Babe::CommandParser::ArgVector& args);
  virtual ~UpdateUserStatusCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mStatus;
  std::string mStringified;
};

#endif		// ! __UPDATEUSERSTATUSCMD_HPP__

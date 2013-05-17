//
// DeleteContactCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 23:25:06 2011 alexandre champion
// Last update Fri Dec  2 17:45:47 2011 alexandre champion
//

#ifndef		__DELETECONTACTCMD_HPP__
# define	__DELETECONTACTCMD_HPP__

# include <string>
# include <Babe.hpp>

class DeleteContactCmd : public Babe::ICommand
{
public:
  DeleteContactCmd(std::string const& login);
  DeleteContactCmd(Babe::CommandParser::ArgVector& args);
  virtual ~DeleteContactCmd();
  virtual void exec();
  virtual void unexec();
  virtual bool isUndoable() const;
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mLogin;
  std::string mStringified;
};

#endif		// ! __DELETECONTACTCMD_HPP__

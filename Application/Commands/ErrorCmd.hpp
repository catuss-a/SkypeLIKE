//
// ErrorCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Thu Dec  1 23:30:05 2011 alexandre champion
// Last update Thu Dec  1 23:30:55 2011 alexandre champion
//

#ifndef		__ERRORCMD_HPP__
# define	__ERRORCMD_HPP__

# include <string>
# include <Babe.hpp>

class ErrorCmd : public Babe::ICommand
{
public:
  ErrorCmd(std::string const& errorMessage);
  ErrorCmd(Babe::CommandParser::ArgVector& args);
  virtual ~ErrorCmd();
  virtual void exec();
  virtual std::string const& getName() const;
  virtual std::string const& stringify();

private:
  std::string mName;
  std::string mErrorMessage;
  std::string mStringified;
};

#endif		// ! __ERRORCMD_HPP__

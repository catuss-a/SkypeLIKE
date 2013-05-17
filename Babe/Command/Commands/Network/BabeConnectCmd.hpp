//
// BabeConnectCmd.hpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Fri Dec  2 19:21:16 2011 alexandre champion
// Last update Fri Dec  2 19:58:38 2011 alexandre champion
//

#ifndef		__BABE_CONNECTCMD_HPP__
# define	__BABE_CONNECTCMD_HPP__

# include <string>
# include "BabeICommand.hpp"
# include "BabeNetworkManagerImpl.hpp"

namespace Babe
{

  class BABE_DLLREQ ConnectCmd : public ICommand
  {
  public:
    ConnectCmd(std::string const& hostName, std::string const& port, std::string const& family);
    ConnectCmd(CommandParser::ArgVector& args);
    virtual ~ConnectCmd();
    virtual void exec();
    virtual std::string const& getName() const;
    virtual std::string const& stringify();

  private:
    NetworkManagerImpl::eConnectionFamily familyFromString(std::string const& family);

  private:
    std::string	mName;
    std::string mHostName;
    std::string mPort;
    std::string mFamilyStr;
    NetworkManagerImpl::eConnectionFamily	mFamily;
    std::string mStringified;
  };

} // End of namespace Babe

#endif		// ! __BABE_CONNECTCMD_HPP__

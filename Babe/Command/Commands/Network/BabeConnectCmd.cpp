//
// BabeConnectCmd.cpp for  in /home/champi_d//AdvancedCPP/Babel/Mercurial/babel-2014-champi_d
// 
// Made by alexandre champion
// Login   <champi_d@epitech.net>
// 
// Started on  Fri Dec  2 19:21:20 2011 alexandre champion
// Last update Fri Dec  2 20:30:07 2011 alexandre champion
//

#include "BabeConnectCmd.hpp"
#include "BabeApplicationManager.hpp"
#include "BabePluginManager.hpp"
#include "BabeCommandManager.hpp"
#include "BabeNetworkManager.hpp"

namespace Babe
{

  ConnectCmd::ConnectCmd(std::string const& hostName, std::string const& port, std::string const& family)
    : ICommand(HIGH),
      mName("connect"),
      mHostName(hostName),
      mPort(port),
      mFamilyStr(family),
      mFamily(familyFromString(family))
  {
  }

  ConnectCmd::ConnectCmd(CommandParser::ArgVector& args)
    : ICommand(HIGH),
	  mName("connect")
  {
    if (args.size() < 3)
      return ;
    mHostName = args[0];
    mPort = args[1];
    mFamilyStr = args[2];
    mFamily = familyFromString(args[2]);
  }

  ConnectCmd::~ConnectCmd()
  {
  }

  void ConnectCmd::exec()
  {
    if (NetworkManager::getSingletonPtr()->connect(mHostName, mPort, mFamily))
      CommandManager::getSingletonPtr()->setReturnMessage("Connection succeeded " + mHostName + " " + mPort + " " + mFamilyStr);
    else
      CommandManager::getSingletonPtr()->setReturnMessage("Connection failed " + mHostName + " " + mPort + " " + mFamilyStr);
  }

  std::string const& ConnectCmd::getName() const
  {
    return mName;
  }

  std::string const& ConnectCmd::stringify()
  {
    mStringified = mName + " " + mHostName + " " + mPort + " " + mFamilyStr;
    return mStringified;
  }

  NetworkManagerImpl::eConnectionFamily ConnectCmd::familyFromString(std::string const& family)
  {
    NetworkManagerImpl::eConnectionFamily efamily;
    if ((family == "ipv6") || (family == "IPV6") || (family == "IPv6"))
      efamily = NetworkManagerImpl::IPV6;
    else
      efamily = NetworkManagerImpl::IPV4;
    return efamily;
  }

} // End of namespace Babe

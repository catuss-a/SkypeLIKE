
#ifndef		__BABE_PLUGINTPL_HPP__
# define	__BABE_PLUGINTPL_HPP__

# include <string>
# include "BabeSystemImpl.hpp"
# include "BabeNonCopyable.hpp"

namespace Babe
{

  template <class TSystemImpl>
  class PluginTpl : public Plugin
  {
  public:
    PluginTpl(SystemImplFactory* factory);
    virtual ~PluginTpl() {}
    static Plugin* createInstance();
    static bool destroyInstance(Plugin* plugin);
  };

  template <class TSystemImpl>
  PluginTpl<TSystemImpl>::PluginTpl(SystemImplFactory* factory)
    : Plugin(factory)
  {
  }

  template <class TSystemImpl>
  Plugin* PluginTpl<TSystemImpl>::createInstance()
  {
    return new PluginTpl(static_cast<SystemImplFactory*>(new SystemImplFactoryTpl<TSystemImpl>));
  }

  template <class TSystemImpl>
  bool PluginTpl<TSystemImpl>::destroyInstance(Plugin* plugin)
  {
    if (!plugin)
      return false;
    delete static_cast<PluginTpl<TSystemImpl>*>(plugin);
    return true;
  }

} // End of namespace Babe

#endif		// ! __BABE_PLUGINTPL_HPP__

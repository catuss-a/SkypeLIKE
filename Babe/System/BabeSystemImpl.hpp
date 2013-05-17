
#ifndef		__BABE_SYSTEMIMPL_HPP__
# define	__BABE_SYSTEMIMPL_HPP__

# include "BabeDef.hpp"
# include "BabeNonCopyable.hpp"

namespace Babe
{

  class BABE_DLLREQ SystemImpl
  {
  public:
    virtual ~SystemImpl() {}
    virtual bool init() = 0;
    virtual void shutdown() = 0;
    virtual void update(float dt) = 0;
  };

  class BABE_DLLREQ SystemImplFactory : public NonCopyable
  {
  public:
    virtual SystemImpl* createSystemImpl() = 0;
  };

  template <class TSystemImpl>
  class BABE_DLLREQ SystemImplFactoryTpl : public SystemImplFactory
  {
    virtual SystemImpl* createSystemImpl()
    {
      return new TSystemImpl;
    }
  };

} // End of namespace Babe

#endif		// ! __BABE_SYSTEMIMPL_HPP__

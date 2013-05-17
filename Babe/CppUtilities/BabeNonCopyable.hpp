
#ifndef		__BABE_NONCOPYABLE_HPP__
# define	__BABE_NONCOPYABLE_HPP__

namespace Babe
{

  class BABE_DLLREQ NonCopyable
  {
  protected:
    NonCopyable() { }
    virtual ~NonCopyable() { }
  private:
    NonCopyable(NonCopyable const& other);
    NonCopyable& operator=(NonCopyable const& other);
  };

} // End of namespace Babe

#endif		// ! __BABE_NONCOPYABLE_HPP__

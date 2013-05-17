
#ifndef		__BABE_SINGLETON_HPP__
#define		__BABE_SINGLETON_HPP__

# include <typeinfo>
# include <iostream>
# include <cstdlib>

#define	ASSERT_SINGLETON(exp, name, where)     		\
  if (exp) {}						\
  else {						\
    std::cerr << "BAD ASSERT_SINGLETON " << name << where << std:: endl;			\
    abort();						\
  }

namespace Babe
{

  template <typename T>
  class Singleton
  {
  private:
    Singleton(Singleton<T> const&);
    Singleton& operator=(Singleton<T> const&);

  public:
    Singleton()
    {
      ASSERT_SINGLETON(!msSingleton, typeid(T).name(), " in constructor");
      msSingleton = static_cast<T*>(this);
    }
    ~Singleton()
    {
      ASSERT_SINGLETON(msSingleton, typeid(T).name(), " in destructor");
      msSingleton = 0;
    }
    static T& getSingleton()
    {
      ASSERT_SINGLETON(msSingleton, typeid(T).name(), " in getSingleton");
      return *msSingleton;
    }
    static T* getSingletonPtr()
    {
      //ASSERT_SINGLETON(msSingleton, typeid(T).name(), " in getSingletonPtr");
      return msSingleton;
    }

  protected: 
    static T* msSingleton;
  };

  template <typename T> T* Singleton<T>::msSingleton = 0;

} // End of namespace Babe

#endif		/* !__BABE_SINGLETON_HPP__ */


#ifndef		__BABE_AUDIOFRAME_HPP__
# define	__BABE_AUDIOFRAME_HPP__

# include "BabeDef.hpp"

namespace Babe
{

  class BABE_DLLREQ AudioFrame
  {
  public:
    enum eState
      {
	RAW,
	ENCODED
      };

  public:
    virtual ~AudioFrame() {}
    eState getState() const { return mState; }
    virtual void encode() = 0;
    virtual void decode() = 0;

  protected:
    eState		mState;
  };

} // End of namespace Babe

#endif		// !__BABE_AUDIOFRAME_HPP__

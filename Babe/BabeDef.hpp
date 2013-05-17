//
// BabeDef.hpp
//
// Made by alexandre champion
// Login   <champi_d@epitech.net>
//

#ifndef		__BABEDEF_HPP__
# define	__BABEDEF_HPP__


# if defined (_WIN32)
# define BABE_WIN32

#  if defined (BABE_DLLEXPORT)
#   define BABE_DLLREQ __declspec(dllexport)
#	define BABE_EXTERN
#  else
#   define BABE_DLLREQ __declspec(dllimport)
#   define BABE_EXTERN extern
#  endif // !BABE_DLLEXPORT

# if defined BABE_WIN32
//disable warnings on extern before template instantiation
# pragma warning (disable : 4231)
# pragma warning (disable : 4251)

# include <string>
// STL forward declaration as expected for dll processing
// see http://support.microsoft.com/kb/168958/en-us
//BABE_EXTERN template class BABE_DLLREQ std::basic_string<char, std::char_traits<char>, std::allocator<char> >;
# endif // ! BABE_WIN32

# endif // !_WIN32



# if defined (__unix__) || defined (__linux__)
# define BABE_UNIX

# define BABE_DLLREQ
# define BABE_EXTERN

# endif // !__unix__ || __linux__



# define BABE_XML_QT



#endif		// ! __BABEDEF_HPP__

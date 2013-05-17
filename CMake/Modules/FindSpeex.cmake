# Finds Speex library
#
# Speex_INCLUDE_DIR - where to find speex.h, etc.
# Speex_LIBRARIES - List of libraries when using Speex.
# Speex_FOUND - True if Speex found.
#

find_path(Speex_INCLUDE_DIR speex/speex.h
/usr/lib
/usr/local/lib
/opt/local/lib
$ENV{SPEEX_DIR}
$ENV{SPEEX_DIR}/include
)

set(Speex_NAMES speex)
find_library(Speex_LIBRARY
NAMES ${Speex_NAMES}
PATHS /usr/lib /usr/local/lib /opt/local/lib $ENV{SPEEX_DIR} $ENV{SPEEX_DIR}/lib
)

if (Speex_INCLUDE_DIR AND Speex_LIBRARY)
set(Speex_FOUND TRUE)
set( Speex_LIBRARIES ${Speex_LIBRARY} )
else (Speex_INCLUDE_DIR AND Speex_LIBRARY)
set(Speex_FOUND FALSE)
set(Speex_LIBRARIES)
endif (Speex_INCLUDE_DIR AND Speex_LIBRARY)

if (Speex_FOUND)
if (NOT Speex_FIND_QUIETLY)
message(STATUS "Found Speex: ${Speex_LIBRARY}")
endif (NOT Speex_FIND_QUIETLY)
else (Speex_FOUND)
if (Speex_FIND_REQUIRED)
message(STATUS "Looked for Speex libraries named ${Speex_NAMES}.")
message(STATUS "Include file detected: [${Speex_INCLUDE_DIR}].")
message(STATUS "Lib file detected: [${Speex_LIBRARY}].")
message(FATAL_ERROR "=========> Could NOT find Speex library")
endif (Speex_FIND_REQUIRED)
endif (Speex_FOUND)

mark_as_advanced(
Speex_LIBRARY
Speex_INCLUDE_DIR
)

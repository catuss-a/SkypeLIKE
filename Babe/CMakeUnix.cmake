if (UNIX)

LIST (
     APPEND BABE_SRC_FILES
     Plugin/Impl/Posix/BabePluginManagerPosixImpl.cpp
     Serialization/Impl/LibXML++/BabeXMLDocumentLibxmlppImpl.cpp     
)

LIST(
	APPEND BABE_INC_DIRS
	Plugin/Impl/Posix/
	Serialization/Impl/LibXML++/
)

if ("${CMAKE_SYSTEM_NAME}" MATCHES ".*BSD")

LIST (
     APPEND BABE_LIBS
     util
     pthread
)

else()

LIST (
     APPEND BABE_LIBS
     dl
     util
     pthread
)

endif()

set (CMAKE_CXX_FLAGS "-W -Wextra -ansi -Wall")

endif (UNIX)

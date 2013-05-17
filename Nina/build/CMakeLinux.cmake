if ("${CMAKE_SYSTEM_NAME}" MATCHES "Linux")

# NINA Library configuration

set (
		NINA_SRC_FILES
		${CMAKE_CURRENT_SOURCE_DIR}/../src/NinaPacket.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../src/NinaAddr.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../src/NinaInetAddr.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../src/NinaIOContainer.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../src/NinaOS.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../src/NinaPollPolicy.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../src/NinaSAP.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../src/NinaSelectPolicy.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../src/NinaSock.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../src/NinaSockIO.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../src/NinaSockStream.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../src/NinaSockDatagram.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../src/NinaSockAcceptor.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../src/NinaSockConnector.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../src/NinaTime.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../src/NinaEpollPolicy.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/../src/NinaError.cpp
)


if (LINUX_PREREQUISITE)
target_link_libraries (nina rt)
endif()

# Compiling informations

set (CMAKE_CXX_FLAGS "-W -Wextra -ansi -Wall -Wno-long-long")
set (CMAKE_CXX_FLAGS_DEBUG "-W -Wall -Wextra -Wno-long-long -ansi -g3 -pedantic")
set (CMAKE_CXX_FLAGS_RELEASE "-W -Wextra -ansi -Wno-long-long -Wno-strict-aliasing -O2 -Wall")

# Install settings

#install (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../doc/api-doc/* DESTINATION share/nina/doc/)
#install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/../doc/api-doc/man/man3/* DESTINATION man/man3/nina/)
#install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/../inc/* DESTINATION include/nina/)
#install (FILES ${CMAKE_CURRENT_SOURCE_DIR}/../lib/${CMAKE_BUILD_TYPE}/* DESTINATION lib/nina/)

set (LINUX_PREREQUISITE "true")
endif ()


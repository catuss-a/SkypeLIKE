cmake_minimum_required (VERSION 2.6)

# Project configuration

project (Babel)

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_BUILD_TYPE})

set (
	BABELSERVER_SRC_FILES

	BabelServer.cpp
	BabelService.cpp
	PacketCrafter.cpp
	DB.cpp
	main.cpp
)

link_directories (
		${CMAKE_CURRENT_SOURCE_DIR}/../Nina/lib/${CMAKE_BUILD_TYPE}
		${CMAKE_CURRENT_SOURCE_DIR}/../${CMAKE_BUILD_TYPE}
)

if (UNIX)
   set (CMAKE_CXX_FLAGS "-Wno-long-long")
endif (UNIX)

add_executable (
	    BabelServer
	    ${BABELSERVER_SRC_FILES}
)

include_directories (
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Nina/inc
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Babe
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Babe/Core/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Babe/Utilities/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Babe/CppUtilities/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Babe/Serialization/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Babe/System/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Babe/Command/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Babe/Plugin/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Babe/Audio/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Babe/Gui/
)

target_link_libraries(BabelServer nina Babe)

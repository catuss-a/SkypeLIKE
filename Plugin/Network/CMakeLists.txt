cmake_minimum_required (VERSION 2.6)

# Project configuration

project (Babe_NinaNetwork)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../CMake/Modules/")
set (LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../)

set (
	BABE_NETWORK_SRC_FILES

	NetworkPluginNina.cpp
	NetworkManagerNinaImpl.cpp
	BabelService.cpp
	AudioService.cpp
	PacketCrafter.cpp
	PacketManager.cpp
)

link_directories (
			${CMAKE_CURRENT_SOURCE_DIR}/../../
			${CMAKE_CURRENT_SOURCE_DIR}/../../Nina/lib/${CMAKE_BUILD_TYPE}/
)

add_library (
	    Babe_NinaNetwork
	    SHARED
	    ${BABE_NETWORK_SRC_FILES}
)

set_source_files_properties (
		${BABE_NETWORK_SRC_FILES}
		PROPERTIES
		COMPILE_FLAGS
		"-DBABE_DLLEXPORT"
)

include_directories (
		    ${CMAKE_CURRENT_SOURCE_DIR}/../../Babe/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../../Babe/Core/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../../Babe/Utilities/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../../Babe/CppUtilities/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../../Babe/Serialization/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../../Babe/System/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../../Babe/Command/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../../Babe/Plugin/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../../Babe/Audio/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../../Babe/Gui/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../../Nina/inc/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../../Server/
)

target_link_libraries(Babe_NinaNetwork Babe nina)

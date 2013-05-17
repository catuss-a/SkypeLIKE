cmake_minimum_required (VERSION 2.6)

# Project configuration

project (Babe)
set (VERSION "0.1 Beta")

set (LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../CMake/Modules/")

set (
	BABE_SRC_FILES

	Core/BabeApplicationManager.cpp
	Core/BabeApplicationUpdateHandler.cpp
	Core/BabeApplicationSettings.cpp

	CppUtilities/BabeHighLevelSetter.cpp

	Utilities/BabeClock.cpp
	Utilities/BabeLogManager.cpp
	Utilities/BabeStringUtils.cpp

	Serialization/BabeXMLDocument.cpp
	Serialization/Impl/QtXml/BabeXMLDocumentQtxmlImpl.cpp

	Command/BabeCommandManager.cpp
	Command/BabeCommands.cpp
	Command/BabeCommandParser.cpp

	Command/Commands/Core/BabeQuitCmd.cpp
	Command/Commands/Core/BabeUndoCmd.cpp
	Command/Commands/Plugin/BabeLoadPluginCmd.cpp
	Command/Commands/Plugin/BabeUnloadPluginCmd.cpp
	Command/Commands/Network/BabeConnectCmd.cpp

	Plugin/BabePlugin.cpp
	Plugin/BabePluginManager.cpp

	System/BabeSystem.cpp
	System/BabeSystemManager.cpp
	System/BabeSystemFactories.cpp

	Audio/BabeAudioManager.cpp

	Codec/BabeCodecManager.cpp

	Gui/BabeGuiManager.cpp
	Gui/BabeGuiManagerImpl.cpp

	Network/BabeNetworkManager.cpp
)

set (
	BABE_INC_DIRS
	
	./
	Core/
	Utilities/
	Serialization/
	Serialization/Impl/QtXml/
	Command/
	Command/Commands/Core
	Command/Commands/Plugin
	Command/Commands/Network
	CppUtilities/
	Plugin/
	System/
	Input/
	Audio/
	Codec/
	Gui/
	Network/
)

find_package (LibXML++ REQUIRED)

find_package(Qt4 COMPONENTS QtXml QtCore REQUIRED)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

message (STATUS "qt dirs ${QT_LIBRARY_DIR}")
link_directories (${QT_LIBRARY_DIRS})

set (BABE_LIBS ${LibXML++_LIBRARIES} ${QT_LIBRARIES})

# CMake includes
include (CMakeWin32.cmake)
include (CMakeUnix.cmake)

include_directories (${BABE_INC_DIRS} ${LibXML++_INCLUDE_DIRS})

add_library (
	    Babe
	    SHARED
	    ${BABE_SRC_FILES}
)

set_source_files_properties (
		${BABE_SRC_FILES}
		PROPERTIES
		COMPILE_FLAGS
		"-DBABE_DLLEXPORT"
)

target_link_libraries(Babe ${BABE_LIBS})

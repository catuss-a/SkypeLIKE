cmake_minimum_required (VERSION 2.6)

# Project configuration

project (Babe_PortAudioAudio)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../CMake/Modules/")
set (LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../)

find_package (PortAudio REQUIRED)

include_directories(${PORTAUDIO_INCLUDE_DIR})

set (
	BABE_AUDIO_SRC_FILES

	AudioPluginPortAudio.cpp
	AudioManagerPortAudioImpl.cpp
	PortAudioFrame.cpp
)

link_directories (${CMAKE_CURRENT_SOURCE_DIR}/../../)

add_library (
	    Babe_PortAudioAudio
	    SHARED
	    ${BABE_AUDIO_SRC_FILES}
)

set_source_files_properties (
		${BABE_AUDIO_SRC_FILES}
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
		    ${CMAKE_CURRENT_SOURCE_DIR}/../../Babe/Codec/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../../Babe/Gui/
)

set(PORTAUDIO_LIBRARIES ${libPortAudio})

target_link_libraries(Babe_PortAudioAudio "${PORTAUDIO_LIBRARIES}")
target_link_libraries(Babe_PortAudioAudio Babe)


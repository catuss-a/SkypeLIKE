cmake_minimum_required (VERSION 2.6)

# Project configuration

project (Babe_SpeexCodec)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../CMake/Modules/")
set (LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../)

find_package (Speex REQUIRED)

include_directories(${SPEEX_INCLUDE_DIR})

set (
	BABE_CODEC_SRC_FILES

	CodecManagerSpeexImpl.cpp
	CodecPluginSpeex.cpp
)

link_directories (${CMAKE_CURRENT_SOURCE_DIR}/../../)

add_library (
	    Babe_SpeexCodec
	    SHARED
	    ${BABE_CODEC_SRC_FILES}
)

set_source_files_properties (
		${BABE_CODEC_SRC_FILES}
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
			${Speex_INCLUDE_DIR}/
)

MESSAGE (STATUS "")
MESSAGE (STATUS "${Speex_INCLUDE_DIR}")
MESSAGE (STATUS "")

set(PORTAUDIO_LIBRARIES ${Speex_LIBRARY})
target_link_libraries(Babe_SpeexCodec "${Speex_LIBRARY}")
target_link_libraries(Babe_SpeexCodec Babe)

cmake_minimum_required (VERSION 2.6)

# Project configuration

project (Babel)

set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../CMake/Modules/")
set (EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../)

set (
	BABEL_SRC_FILES

	main.cpp
	Babel.cpp
	Commands/UserConnectCmd.cpp
	Commands/UserConnectionSucceededCmd.cpp
	Commands/UserConnectionFailedCmd.cpp
	Commands/UserStatusCmd.cpp
	Commands/UpdateUserStatusCmd.cpp
	Commands/AddContactCmd.cpp
	Commands/ContactRequestCmd.cpp
	Commands/AcceptContactRequestCmd.cpp
	Commands/RejectContactRequestCmd.cpp
	Commands/DeleteContactCmd.cpp
	Commands/UnknownContactCmd.cpp
	Commands/RequestCallCmd.cpp
	Commands/CallRequestCmd.cpp
	Commands/AcceptCallCmd.cpp
	Commands/CallAcceptedCmd.cpp
	Commands/RejectCallCmd.cpp
	Commands/CallRejectedCmd.cpp
	Commands/HangUpCallCmd.cpp
	Commands/CallHungUpCmd.cpp
	Commands/SuspendCallCmd.cpp
	Commands/CallSuspendedCmd.cpp
	Commands/ResumeCallCmd.cpp
	Commands/CallResumedCmd.cpp
	Commands/EndCallCmd.cpp
	Commands/ErrorCmd.cpp
	Commands/ConnectionLostCmd.cpp
	Commands/SendTextCmd.cpp
	Commands/ReceiveTextCmd.cpp
)

link_directories (${CMAKE_CURRENT_SOURCE_DIR}/../ ${CMAKE_CURRENT_SOURCE_DIR}/../Nina/lib/${CMAKE_BUILD_TYPE})

add_executable (
	    Babel
	    ${BABEL_SRC_FILES}
)

include_directories (
		    Commands/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Babe/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Babe/Core/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Babe/Utilities/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Babe/CppUtilities/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Babe/Serialization/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Babe/System/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Babe/Command/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Babe/Plugin/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Babe/Audio/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Babe/Gui/
		    ${CMAKE_CURRENT_SOURCE_DIR}/../Nina/inc/
)

target_link_libraries(Babel Babe nina)

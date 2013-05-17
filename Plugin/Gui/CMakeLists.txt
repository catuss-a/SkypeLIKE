CMAKE_MINIMUM_REQUIRED (VERSION 2.6)

PROJECT (Gui)

FIND_PACKAGE (Qt4 REQUIRED)

SET (LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../)

LINK_DIRECTORIES (${CMAKE_CURRENT_SOURCE_DIR}/../../)

SET (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../../CMake/Modules/")

SET (
  Gui_TRANS
  babel_en.ts
  babel_fr.ts
  babel_es.ts
  babel_1337.ts
)

SET (
  Gui_SOURCES
  BabelHelpConsole.cpp
  BabelAboutDialog.cpp
  BabelAddContactDialog.cpp
  BabelConsole.cpp
  BabelConversation.cpp
  BabelLoginWindow.cpp
  BabelMainWindow.cpp
  BabelNotifications.cpp
  BabelConnectionSettings.cpp
  EmoticonFrame.cpp
  GuiManagerQtImpl.cpp
  GuiPluginQt.cpp
  QSingletonApplication.cpp
)

SET (
  Gui_HEADERS
  BabelHelpConsole.hpp
  BabelConnectionSettings.hpp
  BabelAboutDialog.hpp
  BabelAddContactDialog.hpp
  BabelConsole.hpp
  BabelConversation.hpp
  BabelLoginWindow.hpp
  BabelMainWindow.hpp
  EmoticonFrame.hpp
)

SET (
  Gui_FORMS
  babelaboutdialog.ui
  babelconsole.ui
  babeladdcontactdialog.ui
  babelconversation.ui
  babelloginwindow.ui
  babelmainwindow.ui
  babelconnectionsettings.ui
  babelhelpconsole.ui
  emoticonframe.ui
)

SET (
  Gui_RESOURCES
  Resources.qrc
)

SET (
  Babe_DIR
  ../../Babe/
  ../../Babe/Audio
  ../../Babe/Core
  ../../Babe/Command
  ../../Babe/System
  ../../Babe/Utilities
  ../../Babe/Gui
  ../../Babe/Serialization
  ../../Babe/Plugin
  ../../Babe/CppUtilities
)

SET (
  Gui_LIBS
  Babe
)

SET_SOURCE_FILES_PROPERTIES (
		${Gui_SOURCES}
		PROPERTIES
		COMPILE_FLAGS
		"-DBABE_DLLEXPORT"
)

INCLUDE (${QT_USE_FILE})
INCLUDE_DIRECTORIES (${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES (${Babe_DIR})

QT4_WRAP_CPP (Gui_HEADERS_MOC ${Gui_HEADERS})
QT4_WRAP_UI (Gui_FORMS_HEADERS ${Gui_FORMS})
QT4_ADD_RESOURCES (Gui_RESOURCES_RCC ${Gui_RESOURCES})
QT4_ADD_TRANSLATION (Gui_QM ${Gui_TRANS})

ADD_DEFINITIONS (${QT_DEFINITIONS})
ADD_DEFINITIONS (-DQT_PLUGIN)
ADD_DEFINITIONS (-DQT_NO_DEBUG)
ADD_DEFINITIONS (-DQT_SHARED)

ADD_LIBRARY (
  Babe_QtGui SHARED ${Gui_SOURCES}
  ${Gui_HEADERS_MOC}
  ${Gui_FORMS_HEADERS}
  ${Gui_RESOURCES_RCC}
  ${Gui_QM}
  ${}
)

TARGET_LINK_LIBRARIES(Babe_QtGui ${Gui_LIBS} ${QT_LIBRARIES})

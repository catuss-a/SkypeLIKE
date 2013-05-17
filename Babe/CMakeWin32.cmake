if (WIN32)

LIST (
     APPEND BABE_SRC_FILES
     Plugin/Impl/Win32/BabePluginManagerWin32Impl.cpp
)

LIST(
	APPEND BABE_INC_DIRS
	Plugin/Impl/Win32/
)

endif (WIN32)

SkypeLIKE
-=========
-
-Download: [BabelSlide.pdf](https://mega.co.nz/#!s9FyxJjR!lDF6drNEmeRLb8NOKi_BGZmCqn7bK3Ww1NIuaRLZMXo) for more informations

LOG_SKYPELike
=========

ApplicationManager created
ApplicationSettings created
--Using QtXml for serialization (set define in "Babe/BabeDef.hpp")--
ApplicationUpdateHandler created
PluginManager created
PluginManagerPosixImpl created
CommandManager created
Initializing ApplicationManager



/-----------------------------------Loading Plugins---------------------------------\

mPlugManager->loadPlugin(Babe_PortAudioAudio);
Loading plugin: 'libBabe_PortAudioAudio.so'
dlopen libBabe_PortAudioAudio.so: wrong ELF class: ELFCLASS32
ApplicationManager::loadPlugins Babe_PortAudioAudio failed

mPlugManager->loadPlugin(Babe_SpeexCodec);
Loading plugin: 'libBabe_SpeexCodec.so'
CodecPluginSpeex plugin registered.

mPlugManager->loadPlugin(Babe_QtGui);
Loading plugin: 'libBabe_QtGui.so'
dlopen libBabe_QtGui.so: wrong ELF class: ELFCLASS32
ApplicationManager::loadPlugins Babe_QtGui failed

mPlugManager->loadPlugin(Babe_NinaNetwork);
Loading plugin: 'libBabe_NinaNetwork.so'
dlopen libBabe_NinaNetwork.so: wrong ELF class: ELFCLASS32
ApplicationManager::loadPlugins Babe_NinaNetwork failed

\------------------------------------Plugins loaded---------------------------------/





/-----------------Creating and Registering Systems to SystemManager-----------------\

--Builtin systems--
CommandSystem registered to the SystemManager
--End of Builtin systems--
AudioManager created
AudioSystem registered to the SystemManager
CodecManager created
CodecSystem registered to the SystemManager
GuiManager created
GuiSystem registered to the SystemManager
NetworkManager created
NetworkSystem registered to the SystemManager

\------------------Systems Created and Registered to SystemManager------------------/





/---------------------Setting Implementation for Plugin Systems---------------------\

mPlugManager->initializePlugin(AudioPluginPortAudio);
PluginManagerPosixImpl::initializePlugin("AudioPluginPortAudio");
Couldn't find the plugin 'AudioPluginPortAudio'
AudioPluginPortAudio not found

mPlugManager->initializePlugin(CodecPluginSpeex);
PluginManagerPosixImpl::initializePlugin("CodecPluginSpeex");
SystemManager::setSystemImpl("CodecSystem", impl);
CodecPluginSpeex plugin initialized.

mPlugManager->initializePlugin(GuiPluginQt);
PluginManagerPosixImpl::initializePlugin("GuiPluginQt");
Couldn't find the plugin 'GuiPluginQt'
GuiPluginQt not found

mPlugManager->initializePlugin(NetworkPluginNina);
PluginManagerPosixImpl::initializePlugin("NetworkPluginNina");
Couldn't find the plugin 'NetworkPluginNina'
NetworkPluginNina not found

\--------------------Implementation of Plugin Systems Are Now Set-------------------/





/------------------Registering Systems to ApplicationUpdateHandler------------------\

AudioSystem registered to the ApplicationUpdateHandler.
CodecSystem registered to the ApplicationUpdateHandler.
CommandSystem registered to the ApplicationUpdateHandler.
GuiSystem registered to the ApplicationUpdateHandler.
NetworkSystem registered to the ApplicationUpdateHandler.

\-------------------Systems Registered to ApplicationUpdateHandler------------------/





/--------------------------------Initializing Systems-------------------------------\

NetworkManagerDummyImpl initialized
AudioManagerDummyImpl initialized
CodecManagerSpeexImpl initialized
CommandManager initialized
GuiManagerDummyImpl initialized

\--------------------------------Systems Initialized--------------------------------/





/-----------------------------------Loading Assets----------------------------------\


\-----------------------------------Assets loaded-----------------------------------/




**************************[ The engine has started running ]*************************

|> No GUI. Here is a console access
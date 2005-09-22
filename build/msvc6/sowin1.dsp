# Microsoft Developer Studio Project File - Name="sowin@SOWIN_MAJOR_VERSION@" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE
!MESSAGE NMAKE /f "sowin@SOWIN_MAJOR_VERSION@.mak".
!MESSAGE
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "sowin@SOWIN_MAJOR_VERSION@.mak" CFG="sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)" (based on "Win32 (x86) Static Library")
!MESSAGE "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)" (based on "Win32 (x86) Static Library")
!MESSAGE "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "SOWIN_DEBUG=0" @SOWIN_DSP_DEFS@ @SOWIN_DSP_INCS@ /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "SOWIN_DEBUG=0" @SOWIN_DSP_DEFS@ @SOWIN_DSP_INCS@ /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 @SOWIN_DSP_LIBS@ /nologo /dll /machine:I386
# ADD LINK32 @SOWIN_DSP_LIBS@ /nologo /dll /machine:I386 /out:"sowin@SOWIN_MAJOR_VERSION@.dll" /opt:nowin98
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=install-dll-release.bat
# End Special Build Tool

!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "SOWIN_DEBUG=1" @SOWIN_DSP_DEFS@ @SOWIN_DSP_INCS@ /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "SOWIN_DEBUG=1" @SOWIN_DSP_DEFS@ @SOWIN_DSP_INCS@ /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 @SOWIN_DSP_LIBS@ /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 @SOWIN_DSP_LIBS@ /nologo /dll /debug /machine:I386 /pdbtype:sept /out:"sowin@SOWIN_MAJOR_VERSION@d.dll"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=install-dll-debug.bat
# End Special Build Tool

!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "StaticRelease"
# PROP BASE Intermediate_Dir "StaticRelease"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "StaticRelease"
# PROP Intermediate_Dir "StaticRelease"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_LIB" /D "SOWIN_DEBUG=0" @SOWIN_LIB_DSP_DEFS@ @SOWIN_DSP_INCS@ /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_LIB" /D "SOWIN_DEBUG=0" @SOWIN_LIB_DSP_DEFS@ @SOWIN_DSP_INCS@ /YX /FD /c
# ADD BASE RSC /l 0x414 /d "NDEBUG"
# ADD RSC /l 0x414 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /machine:I386 /out:"sowin@SOWIN_MAJOR_VERSION@s.lib"
# ADD LIB32 /nologo /machine:I386 /out:"sowin@SOWIN_MAJOR_VERSION@s.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=install-lib-release.bat
# End Special Build Tool

!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "StaticDebug"
# PROP BASE Intermediate_Dir "StaticDebug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "StaticDebug"
# PROP Intermediate_Dir "StaticDebug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_LIB" /D "SOWIN_DEBUG=1" @SOWIN_LIB_DSP_DEFS@ @SOWIN_DSP_INCS@ /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_LIB" /D "SOWIN_DEBUG=1" @SOWIN_LIB_DSP_DEFS@ @SOWIN_DSP_INCS@ /YX /FD /c
# ADD BASE RSC /l 0x414 /d "_DEBUG"
# ADD RSC /l 0x414 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /machine:I386 /out:"sowin@SOWIN_MAJOR_VERSION@sd.lib"
# ADD LIB32 /nologo /machine:I386 /out:"sowin@SOWIN_MAJOR_VERSION@sd.lib"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=install-lib-debug.bat
# End Special Build Tool
!ENDIF

# Begin Target

# Name "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# Name "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# Name "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# Name "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;ic;icc"
# Begin Source File

SOURCE=c:\Work\source\SoWin\src\Inventor\Win\devices\SoWinDevice.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\src\Inventor\Win\devices\SoWinInputFocus.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\src\Inventor\Win\devices\SoWinKeyboard.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\src\Inventor\Win\devices\SoWinMouse.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\src\Inventor\Win\devices\SoWinSpaceball.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\devices\spwinput_x11.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\devices\spwinput_win32.c
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\devices\SoWinDeviceCommon.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\devices\SoWinInputFocusCommon.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\devices\SoWinKeyboardCommon.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\devices\SoWinMouseCommon.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\devices\SoWinSpaceballCommon.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\devices"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\editors\SoWinColorEditor.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\editors"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\editors"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\editors"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\editors"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\editors\SoWinMaterialEditor.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\editors"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\editors"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\editors"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\editors"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\engines\Engines.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\engines"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\engines"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\engines"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\engines"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\engines\RadioGroup.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\engines"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\engines"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\engines"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\engines"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\engines\Format.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\engines"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\engines"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\engines"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\engines"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\nodes\Nodes.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\nodes\SceneTexture2.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\nodes\ViewportFix.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\nodes\ViewpointWrapper.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\nodes\Pane.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\nodes\Position.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\nodes\Translation.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\nodes\Frame.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\nodes\Image.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\nodes\Label.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\nodes\ToggleButton.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\nodes\RadioButton.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=c:\Work\source\SoWin\build\msvc6\src\Inventor\Win\nodes\ClickCounter.cpp
!IF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\nodes"
!ELSEIF  "$(CFG)" == "sowin@SOWIN_MAJOR_VERSION@ - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\nodes"
!ENDIF 
# End Source File

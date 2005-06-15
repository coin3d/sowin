# Microsoft Developer Studio Project File - Name="sowin1" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=sowin1 - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE
!MESSAGE NMAKE /f "sowin1.mak".
!MESSAGE
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "sowin1.mak" CFG="sowin1 - Win32 Debug"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "sowin1 - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "sowin1 - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sowin1 - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "SOWIN_DEBUG=0" /D "HAVE_CONFIG_H" /D "SOWIN_MAKE_DLL" /D "SOWIN_INTERNAL" /D "COIN_DLL" /I ".\src" /I ".\data" /I "..\..\src" /I "$(COINDIR)\include" /I "$(COINDIR)\include\Inventor\annex" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O1 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "SOWIN_DEBUG=0" /D "HAVE_CONFIG_H" /D "SOWIN_MAKE_DLL" /D "SOWIN_INTERNAL" /D "COIN_DLL" /I ".\src" /I ".\data" /I "..\..\src" /I "$(COINDIR)\include" /I "$(COINDIR)\include\Inventor\annex" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 $(COINDIR)\lib\coin2.lib opengl32.lib gdi32.lib winmm.lib user32.lib /nologo /dll /machine:I386
# ADD LINK32 $(COINDIR)\lib\coin2.lib opengl32.lib gdi32.lib winmm.lib user32.lib /nologo /dll /machine:I386 /out:"sowin1.dll" /opt:nowin98
# SUBTRACT LINK32 /pdb:none
# Begin Special Build Tool
SOURCE=
PostBuild_Cmds=installsowin.bat
# End Special Build Tool

!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "SOWIN_DEBUG=1" /D "HAVE_CONFIG_H" /D "SOWIN_MAKE_DLL" /D "SOWIN_INTERNAL" /D "COIN_DLL" /I ".\src" /I ".\data" /I "..\..\src" /I "$(COINDIR)\include" /I "$(COINDIR)\include\Inventor\annex" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "SOWIN_DEBUG=1" /D "HAVE_CONFIG_H" /D "SOWIN_MAKE_DLL" /D "SOWIN_INTERNAL" /D "COIN_DLL" /I ".\src" /I ".\data" /I "..\..\src" /I "$(COINDIR)\include" /I "$(COINDIR)\include\Inventor\annex" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 $(COINDIR)\lib\coin2d.lib opengl32.lib gdi32.lib winmm.lib user32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 $(COINDIR)\lib\coin2d.lib opengl32.lib gdi32.lib winmm.lib user32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept /out:"sowin1d.dll"
# Begin Special Build Tool
SOURCE=
PostBuild_Cmds=installsowin.bat
# End Special Build Tool

!ENDIF

# Begin Target

# Name "sowin1 - Win32 Release"
# Name "sowin1 - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;ic;icc"
# Begin Source File

SOURCE=..\..\src\Inventor\Win\devices\SoWinDevice.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\devices\SoWinInputFocus.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\devices\SoWinKeyboard.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\devices\SoWinMouse.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\devices\SoWinSpaceball.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\spwinput_x11.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\spwinput_win32.c
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\SoWinDeviceCommon.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\SoWinInputFocusCommon.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\SoWinKeyboardCommon.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\SoWinMouseCommon.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\SoWinSpaceballCommon.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\devices"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\editors\SoWinColorEditor.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\editors"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\editors"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\editors\SoWinMaterialEditor.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\editors"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\editors"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\engines\Engines.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\engines"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\engines"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\engines\RadioGroup.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\engines"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\engines"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\engines\Format.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\engines"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\engines"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\Nodes.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SceneTexture2.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\ViewportFix.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\ViewpointWrapper.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\Pane.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\Position.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\Translation.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\Frame.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\Image.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\Label.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\ToggleButton.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\RadioButton.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\ClickCounter.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\Slider1.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\Slider2.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\ColorEditor.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\MaterialEditor.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\nodes"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\viewers\FullViewer.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\viewers"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\viewers\ExaminerViewer.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\viewers"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\viewers\PlaneViewer.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\viewers"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\viewers\SoWinViewer.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\viewers"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\viewers\SoWinConstrainedViewer.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\viewers"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\viewers\SoWinFlyViewer.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\viewers"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\viewers\SoWinFullViewer.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\viewers"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\viewers\SoWinExaminerViewer.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\viewers"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\viewers\SoWinPlaneViewer.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\viewers"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\widgets\SoWinThumbWheel.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\widgets"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\widgets"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\widgets\WinNativePopupMenu.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\widgets"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\widgets"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\widgets\SoWinBitmapButton.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\widgets"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\widgets"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\widgets\SoAnyThumbWheel.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\widgets"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\widgets"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\widgets\SoWinPopupMenu.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\widgets"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\widgets"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\SoWin.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\Win"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\SoWinComponent.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\Win"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\SoWinGLWidget.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\Win"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\Win32API.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\Win"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\SoAny.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\Win"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\SoWinCursor.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\Win"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\SoWinObject.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\Win"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\SoWinCommon.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\Win"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\SoWinComponentCommon.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\Win"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\SoWinGLWidgetCommon.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\Win"
!ENDIF 
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\SoWinRenderArea.cpp
!IF  "$(CFG)" == "sowin1 - Win32 Release"
# PROP Intermediate_Dir "Release\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 Debug"
# PROP Intermediate_Dir "Debug\Win"
!ENDIF 
# End Source File
# End Group
# Begin Group "Public Headers"

# PROP Default_Filter "h"
# Begin Source File

SOURCE=src\Inventor\Win\devices\SoWinDevice.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\devices\SoWinInputFocus.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\devices\SoWinKeyboard.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\devices\SoWinMouse.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\devices\SoWinSpaceball.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\editors\SoWinColorEditor.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\editors\SoWinMaterialEditor.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\nodes\SoGuiColorEditor.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\nodes\SoGuiMaterialEditor.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\viewers\SoWinViewer.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\viewers\SoWinConstrainedViewer.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\viewers\SoWinFullViewer.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\viewers\SoWinExaminerViewer.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\viewers\SoWinFlyViewer.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\viewers\SoWinPlaneViewer.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\widgets\SoWinPopupMenu.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\SoWin.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\SoWinBasic.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\SoWinObject.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\SoWinCursor.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\SoWinComponent.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\SoWinGLWidget.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\SoWinRenderArea.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\SoWinColorEditor.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\SoWinMaterialEditor.h
# End Source File
# End Group
# Begin Group "Private Headers"

# PROP Default_Filter "h;ic;icc"
# Begin Source File

SOURCE=.\src\config.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\SoGuiDeviceP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\SoGuiInputFocusP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\SoGuiKeyboardP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\SoGuiMouseP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\SoGuiSpaceballP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\engines\SoGuiEngines.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\engines\SoGuiFormat.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\engines\SoGuiRadioGroup.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiClickCounter.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiFrame.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiImage.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiLabel.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiNodes.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiPane.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiPosition.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiRadioButton.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiSceneTexture2.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiSlider1.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiSlider2.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiToggleButton.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiTranslation.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiViewpointWrapper.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiViewportFix.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\SoGuiComponentP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\SoGuiGLWidgetP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\SoGuiP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\viewers\SoGuiExaminerViewerP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\viewers\SoGuiFullViewerP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\viewers\SoGuiPlaneViewerP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\sowindefs.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\config.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\SoGuiDeviceP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\SoGuiInputFocusP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\SoGuiKeyboardP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\SoGuiMouseP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\SoGuiSpaceballP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\engines\SoGuiEngines.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\engines\SoGuiFormat.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\engines\SoGuiRadioGroup.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiClickCounter.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiFrame.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiImage.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiLabel.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiNodes.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiPane.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiPosition.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiRadioButton.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiSceneTexture2.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiSlider1.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiSlider2.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiToggleButton.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiTranslation.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiViewpointWrapper.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SoGuiViewportFix.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\SoGuiComponentP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\SoGuiGLWidgetP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\SoGuiP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\viewers\SoGuiExaminerViewerP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\viewers\SoGuiFullViewerP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\viewers\SoGuiPlaneViewerP.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\sowindefs.h
# PROP Exclude_From_Build 1
# End Source File
# End Group
# End Target
# End Project

# Microsoft Developer Studio Project File - Name="sowin1" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=sowin1 - Win32 DLL (Release)
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE
!MESSAGE NMAKE /f "sowin1.mak".
!MESSAGE
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE
!MESSAGE NMAKE /f "sowin1.mak" CFG="sowin1 - Win32 DLL (Debug)"
!MESSAGE
!MESSAGE Possible choices for configuration are:
!MESSAGE
!MESSAGE "sowin1 - Win32 LIB (Release)" (based on "Win32 (x86) Static Library")
!MESSAGE "sowin1 - Win32 LIB (Debug)" (based on "Win32 (x86) Static Library")
!MESSAGE "sowin1 - Win32 DLL (Release)" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "sowin1 - Win32 DLL (Debug)" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

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
MTL=midl.exe
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /Ox /Gy /Zi /I "src" /I "data" /I "..\..\src" /I "$(COINDIR)\include" /I "$(COINDIR)\include\Inventor\annex" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_LIB" /D SOWIN_DEBUG=0  /D "HAVE_CONFIG_H" /D "SOWIN_INTERNAL" /D "COIN_NOT_DLL" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Ox /Gy /Zi /I "src" /I "data" /I "..\..\src" /I "$(COINDIR)\include" /I "$(COINDIR)\include\Inventor\annex" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_LIB" /D SOWIN_DEBUG=0  /D "HAVE_CONFIG_H" /D "SOWIN_INTERNAL" /D "COIN_NOT_DLL" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x414 /d "NDEBUG"
# ADD RSC /l 0x414 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /machine:I386 /out:"sowin1s.lib"
# ADD LIB32 /nologo /machine:I386 /out:"sowin1s.lib"

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

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
MTL=midl.exe
CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /GX /GZ /Od /Zi /I "src" /I "data" /I "..\..\src" /I "$(COINDIR)\include" /I "$(COINDIR)\include\Inventor\annex" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_LIB" /D SOWIN_DEBUG=1  /D "HAVE_CONFIG_H" /D "SOWIN_INTERNAL" /D "COIN_NOT_DLL" /FD /c
# ADD CPP /nologo /MDd /W3 /GX /GZ /Od /Zi /I "src" /I "data" /I "..\..\src" /I "$(COINDIR)\include" /I "$(COINDIR)\include\Inventor\annex" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_LIB" /D SOWIN_DEBUG=1  /D "HAVE_CONFIG_H" /D "SOWIN_INTERNAL" /D "COIN_NOT_DLL" /FD /c
RSC=rc.exe
# ADD BASE RSC /l 0x414 /d "_DEBUG"
# ADD RSC /l 0x414 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo /machine:I386 /out:"sowin1sd.lib"
# ADD LIB32 /nologo /machine:I386 /out:"sowin1sd.lib"

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

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
CPP=cl.exe
# ADD BASE CPP /nologo /MD /W3 /GX /Ox /Gy /Zi /I "src" /I "data" /I "..\..\src" /I "$(COINDIR)\include" /I "$(COINDIR)\include\Inventor\annex" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D SOWIN_DEBUG=0 /D "HAVE_CONFIG_H" /D "SOWIN_MAKE_DLL" /D "SOWIN_INTERNAL" /D "COIN_DLL" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Ox /Gy /Zi /I "src" /I "data" /I "..\..\src" /I "$(COINDIR)\include" /I "$(COINDIR)\include\Inventor\annex" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D SOWIN_DEBUG=0 /D "HAVE_CONFIG_H" /D "SOWIN_MAKE_DLL" /D "SOWIN_INTERNAL" /D "COIN_DLL" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
RCS=rc.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 $(COINDIR)\lib\coin3.lib opengl32.lib gdi32.lib winmm.lib user32.lib /nologo /dll /release /machine:I386 /pdbtype:sept
# ADD LINK32 $(COINDIR)\lib\coin3.lib opengl32.lib gdi32.lib winmm.lib user32.lib /nologo /dll /release /machine:I386 /pdbtype:sept /out:"sowin1.dll" /opt:nowin98
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

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
CPP=cl.exe
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /GZ /Zi /Od /I "src" /I "data" /I "..\..\src" /I "$(COINDIR)\include" /I "$(COINDIR)\include\Inventor\annex" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D SOWIN_DEBUG=1 /D "HAVE_CONFIG_H" /D "SOWIN_MAKE_DLL" /D "SOWIN_INTERNAL" /D "COIN_DLL" /FD /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /GZ /Zi /Od /I "src" /I "data" /I "..\..\src" /I "$(COINDIR)\include" /I "$(COINDIR)\include\Inventor\annex" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D SOWIN_DEBUG=1 /D "HAVE_CONFIG_H" /D "SOWIN_MAKE_DLL" /D "SOWIN_INTERNAL" /D "COIN_DLL" /FD /c
MTL=midl.exe
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
RCS=rc.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 $(COINDIR)\lib\coin3d.lib opengl32.lib gdi32.lib winmm.lib user32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 $(COINDIR)\lib\coin3d.lib opengl32.lib gdi32.lib winmm.lib user32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept /out:"sowin1d.dll" /opt:nowin98

!ENDIF

# Begin Target

# Name "sowin1 - Win32 DLL (Release)"
# Name "sowin1 - Win32 DLL (Debug)"
# Name "sowin1 - Win32 LIB (Release)"
# Name "sowin1 - Win32 LIB (Debug)"
# Begin Group "Documents"
# PROP Default_Filter ";txt"
# Begin Source File

SOURCE=..\..\README
# End Source File
# Begin Source File

SOURCE=..\..\NEWS
# End Source File
# Begin Source File

SOURCE=..\..\LICENSE.GPL
# End Source File
# Begin Source File

SOURCE=..\..\COPYING
# End Source File
# Begin Source File

SOURCE=..\..\ChangeLog
# End Source File
# End Group
# Begin Group "Template Files"
# PROP Default_Filter "in"
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\gl.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\gl.h.in

"src\Inventor\Win\common\gl.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\gl.h.in:src\Inventor\Win\common\gl.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\common\gl.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\gl.h.in:src\Inventor\Win\common\gl.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\common\gl.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\gl.h.in:src\Inventor\Win\common\gl.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\common\gl.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\gl.h.in:src\Inventor\Win\common\gl.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\devices\SoGuiDeviceP.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\devices\SoGuiDeviceP.h.in

"src\Inventor\Win\devices\SoGuiDeviceP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiDeviceP.h.in:src\Inventor\Win\devices\SoGuiDeviceP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoGuiDeviceP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiDeviceP.h.in:src\Inventor\Win\devices\SoGuiDeviceP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoGuiDeviceP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiDeviceP.h.in:src\Inventor\Win\devices\SoGuiDeviceP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoGuiDeviceP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiDeviceP.h.in:src\Inventor\Win\devices\SoGuiDeviceP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\devices\SoGuiInputFocusP.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\devices\SoGuiInputFocusP.h.in

"src\Inventor\Win\devices\SoGuiInputFocusP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiInputFocusP.h.in:src\Inventor\Win\devices\SoGuiInputFocusP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoGuiInputFocusP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiInputFocusP.h.in:src\Inventor\Win\devices\SoGuiInputFocusP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoGuiInputFocusP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiInputFocusP.h.in:src\Inventor\Win\devices\SoGuiInputFocusP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoGuiInputFocusP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiInputFocusP.h.in:src\Inventor\Win\devices\SoGuiInputFocusP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\devices\SoGuiKeyboardP.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\devices\SoGuiKeyboardP.h.in

"src\Inventor\Win\devices\SoGuiKeyboardP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiKeyboardP.h.in:src\Inventor\Win\devices\SoGuiKeyboardP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoGuiKeyboardP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiKeyboardP.h.in:src\Inventor\Win\devices\SoGuiKeyboardP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoGuiKeyboardP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiKeyboardP.h.in:src\Inventor\Win\devices\SoGuiKeyboardP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoGuiKeyboardP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiKeyboardP.h.in:src\Inventor\Win\devices\SoGuiKeyboardP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\devices\SoGuiMouseP.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\devices\SoGuiMouseP.h.in

"src\Inventor\Win\devices\SoGuiMouseP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiMouseP.h.in:src\Inventor\Win\devices\SoGuiMouseP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoGuiMouseP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiMouseP.h.in:src\Inventor\Win\devices\SoGuiMouseP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoGuiMouseP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiMouseP.h.in:src\Inventor\Win\devices\SoGuiMouseP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoGuiMouseP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiMouseP.h.in:src\Inventor\Win\devices\SoGuiMouseP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\devices\SoGuiSpaceballP.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\devices\SoGuiSpaceballP.h.in

"src\Inventor\Win\devices\SoGuiSpaceballP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiSpaceballP.h.in:src\Inventor\Win\devices\SoGuiSpaceballP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoGuiSpaceballP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiSpaceballP.h.in:src\Inventor\Win\devices\SoGuiSpaceballP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoGuiSpaceballP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiSpaceballP.h.in:src\Inventor\Win\devices\SoGuiSpaceballP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoGuiSpaceballP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiSpaceballP.h.in:src\Inventor\Win\devices\SoGuiSpaceballP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\devices\SoGuiDevice.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\devices\SoGuiDevice.h.in

"src\Inventor\Win\devices\SoWinDevice.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiDevice.h.in:src\Inventor\Win\devices\SoWinDevice.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinDevice.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiDevice.h.in:src\Inventor\Win\devices\SoWinDevice.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinDevice.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiDevice.h.in:src\Inventor\Win\devices\SoWinDevice.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinDevice.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiDevice.h.in:src\Inventor\Win\devices\SoWinDevice.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\devices\SoGuiDevice.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\devices\SoGuiDevice.cpp.in

"src\Inventor\Win\devices\SoWinDeviceCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiDevice.cpp.in:src\Inventor\Win\devices\SoWinDeviceCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinDeviceCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiDevice.cpp.in:src\Inventor\Win\devices\SoWinDeviceCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinDeviceCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiDevice.cpp.in:src\Inventor\Win\devices\SoWinDeviceCommon.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinDeviceCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiDevice.cpp.in:src\Inventor\Win\devices\SoWinDeviceCommon.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\devices\SoGuiInputFocus.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\devices\SoGuiInputFocus.h.in

"src\Inventor\Win\devices\SoWinInputFocus.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiInputFocus.h.in:src\Inventor\Win\devices\SoWinInputFocus.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinInputFocus.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiInputFocus.h.in:src\Inventor\Win\devices\SoWinInputFocus.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinInputFocus.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiInputFocus.h.in:src\Inventor\Win\devices\SoWinInputFocus.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinInputFocus.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiInputFocus.h.in:src\Inventor\Win\devices\SoWinInputFocus.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\devices\SoGuiInputFocus.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\devices\SoGuiInputFocus.cpp.in

"src\Inventor\Win\devices\SoWinInputFocusCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiInputFocus.cpp.in:src\Inventor\Win\devices\SoWinInputFocusCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinInputFocusCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiInputFocus.cpp.in:src\Inventor\Win\devices\SoWinInputFocusCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinInputFocusCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiInputFocus.cpp.in:src\Inventor\Win\devices\SoWinInputFocusCommon.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinInputFocusCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiInputFocus.cpp.in:src\Inventor\Win\devices\SoWinInputFocusCommon.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\devices\SoGuiKeyboard.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\devices\SoGuiKeyboard.h.in

"src\Inventor\Win\devices\SoWinKeyboard.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiKeyboard.h.in:src\Inventor\Win\devices\SoWinKeyboard.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinKeyboard.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiKeyboard.h.in:src\Inventor\Win\devices\SoWinKeyboard.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinKeyboard.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiKeyboard.h.in:src\Inventor\Win\devices\SoWinKeyboard.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinKeyboard.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiKeyboard.h.in:src\Inventor\Win\devices\SoWinKeyboard.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\devices\SoGuiKeyboard.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\devices\SoGuiKeyboard.cpp.in

"src\Inventor\Win\devices\SoWinKeyboardCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiKeyboard.cpp.in:src\Inventor\Win\devices\SoWinKeyboardCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinKeyboardCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiKeyboard.cpp.in:src\Inventor\Win\devices\SoWinKeyboardCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinKeyboardCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiKeyboard.cpp.in:src\Inventor\Win\devices\SoWinKeyboardCommon.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinKeyboardCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiKeyboard.cpp.in:src\Inventor\Win\devices\SoWinKeyboardCommon.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\devices\SoGuiMouse.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\devices\SoGuiMouse.h.in

"src\Inventor\Win\devices\SoWinMouse.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiMouse.h.in:src\Inventor\Win\devices\SoWinMouse.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinMouse.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiMouse.h.in:src\Inventor\Win\devices\SoWinMouse.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinMouse.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiMouse.h.in:src\Inventor\Win\devices\SoWinMouse.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinMouse.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiMouse.h.in:src\Inventor\Win\devices\SoWinMouse.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\devices\SoGuiMouse.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\devices\SoGuiMouse.cpp.in

"src\Inventor\Win\devices\SoWinMouseCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiMouse.cpp.in:src\Inventor\Win\devices\SoWinMouseCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinMouseCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiMouse.cpp.in:src\Inventor\Win\devices\SoWinMouseCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinMouseCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiMouse.cpp.in:src\Inventor\Win\devices\SoWinMouseCommon.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinMouseCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiMouse.cpp.in:src\Inventor\Win\devices\SoWinMouseCommon.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\devices\SoGuiSpaceball.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\devices\SoGuiSpaceball.h.in

"src\Inventor\Win\devices\SoWinSpaceball.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiSpaceball.h.in:src\Inventor\Win\devices\SoWinSpaceball.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinSpaceball.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiSpaceball.h.in:src\Inventor\Win\devices\SoWinSpaceball.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinSpaceball.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiSpaceball.h.in:src\Inventor\Win\devices\SoWinSpaceball.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinSpaceball.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiSpaceball.h.in:src\Inventor\Win\devices\SoWinSpaceball.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\devices\SoGuiSpaceball.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\devices\SoGuiSpaceball.cpp.in

"src\Inventor\Win\devices\SoWinSpaceballCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiSpaceball.cpp.in:src\Inventor\Win\devices\SoWinSpaceballCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinSpaceballCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiSpaceball.cpp.in:src\Inventor\Win\devices\SoWinSpaceballCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinSpaceballCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiSpaceball.cpp.in:src\Inventor\Win\devices\SoWinSpaceballCommon.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\SoWinSpaceballCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\devices\SoGuiSpaceball.cpp.in:src\Inventor\Win\devices\SoWinSpaceballCommon.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\spwinput.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\spwinput.h.in

"src\Inventor\Win\devices\spwinput.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\spwinput.h.in:src\Inventor\Win\devices\spwinput.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\spwinput.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\spwinput.h.in:src\Inventor\Win\devices\spwinput.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\spwinput.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\spwinput.h.in:src\Inventor\Win\devices\spwinput.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\spwinput.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\spwinput.h.in:src\Inventor\Win\devices\spwinput.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\spwinput_win32.c.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\spwinput_win32.c.in

"src\Inventor\Win\devices\spwinput_win32.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\spwinput_win32.c.in:src\Inventor\Win\devices\spwinput_win32.c

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\spwinput_win32.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\spwinput_win32.c.in:src\Inventor\Win\devices\spwinput_win32.c

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\spwinput_win32.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\spwinput_win32.c.in:src\Inventor\Win\devices\spwinput_win32.c

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\spwinput_win32.c" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\spwinput_win32.c.in:src\Inventor\Win\devices\spwinput_win32.c

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\spwinput_win32.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\spwinput_win32.h.in

"src\Inventor\Win\devices\spwinput_win32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\spwinput_win32.h.in:src\Inventor\Win\devices\spwinput_win32.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\spwinput_win32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\spwinput_win32.h.in:src\Inventor\Win\devices\spwinput_win32.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\spwinput_win32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\spwinput_win32.h.in:src\Inventor\Win\devices\spwinput_win32.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\spwinput_win32.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\spwinput_win32.h.in:src\Inventor\Win\devices\spwinput_win32.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\spwinput_x11.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\spwinput_x11.cpp.in

"src\Inventor\Win\devices\spwinput_x11.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\spwinput_x11.cpp.in:src\Inventor\Win\devices\spwinput_x11.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\spwinput_x11.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\spwinput_x11.cpp.in:src\Inventor\Win\devices\spwinput_x11.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\spwinput_x11.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\spwinput_x11.cpp.in:src\Inventor\Win\devices\spwinput_x11.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\devices\spwinput_x11.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\spwinput_x11.cpp.in:src\Inventor\Win\devices\spwinput_x11.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\editors\SoGuiColorEditor.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\editors\SoGuiColorEditor.cpp.in

"src\Inventor\Win\editors\SoWinColorEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiColorEditor.cpp.in:src\Inventor\Win\editors\SoWinColorEditor.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\editors\SoWinColorEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiColorEditor.cpp.in:src\Inventor\Win\editors\SoWinColorEditor.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\editors\SoWinColorEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiColorEditor.cpp.in:src\Inventor\Win\editors\SoWinColorEditor.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\editors\SoWinColorEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiColorEditor.cpp.in:src\Inventor\Win\editors\SoWinColorEditor.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\editors\SoGuiColorEditor.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\editors\SoGuiColorEditor.h.in

"src\Inventor\Win\editors\SoWinColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiColorEditor.h.in:src\Inventor\Win\editors\SoWinColorEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\editors\SoWinColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiColorEditor.h.in:src\Inventor\Win\editors\SoWinColorEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\editors\SoWinColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiColorEditor.h.in:src\Inventor\Win\editors\SoWinColorEditor.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\editors\SoWinColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiColorEditor.h.in:src\Inventor\Win\editors\SoWinColorEditor.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\editors\SoGuiMaterialEditor.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\editors\SoGuiMaterialEditor.cpp.in

"src\Inventor\Win\editors\SoWinMaterialEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiMaterialEditor.cpp.in:src\Inventor\Win\editors\SoWinMaterialEditor.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\editors\SoWinMaterialEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiMaterialEditor.cpp.in:src\Inventor\Win\editors\SoWinMaterialEditor.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\editors\SoWinMaterialEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiMaterialEditor.cpp.in:src\Inventor\Win\editors\SoWinMaterialEditor.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\editors\SoWinMaterialEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiMaterialEditor.cpp.in:src\Inventor\Win\editors\SoWinMaterialEditor.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\editors\SoGuiMaterialEditor.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\editors\SoGuiMaterialEditor.h.in

"src\Inventor\Win\editors\SoWinMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiMaterialEditor.h.in:src\Inventor\Win\editors\SoWinMaterialEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\editors\SoWinMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiMaterialEditor.h.in:src\Inventor\Win\editors\SoWinMaterialEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\editors\SoWinMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiMaterialEditor.h.in:src\Inventor\Win\editors\SoWinMaterialEditor.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\editors\SoWinMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiMaterialEditor.h.in:src\Inventor\Win\editors\SoWinMaterialEditor.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\engines\Engines.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\engines\Engines.cpp.in

"src\Inventor\Win\engines\Engines.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\Engines.cpp.in:src\Inventor\Win\engines\Engines.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\engines\Engines.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\Engines.cpp.in:src\Inventor\Win\engines\Engines.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\engines\Engines.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\Engines.cpp.in:src\Inventor\Win\engines\Engines.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\engines\Engines.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\Engines.cpp.in:src\Inventor\Win\engines\Engines.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\engines\Format.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\engines\Format.cpp.in

"src\Inventor\Win\engines\Format.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\Format.cpp.in:src\Inventor\Win\engines\Format.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\engines\Format.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\Format.cpp.in:src\Inventor\Win\engines\Format.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\engines\Format.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\Format.cpp.in:src\Inventor\Win\engines\Format.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\engines\Format.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\Format.cpp.in:src\Inventor\Win\engines\Format.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\engines\RadioGroup.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\engines\RadioGroup.cpp.in

"src\Inventor\Win\engines\RadioGroup.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\RadioGroup.cpp.in:src\Inventor\Win\engines\RadioGroup.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\engines\RadioGroup.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\RadioGroup.cpp.in:src\Inventor\Win\engines\RadioGroup.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\engines\RadioGroup.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\RadioGroup.cpp.in:src\Inventor\Win\engines\RadioGroup.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\engines\RadioGroup.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\RadioGroup.cpp.in:src\Inventor\Win\engines\RadioGroup.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\engines\Engines.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\engines\Engines.h.in

"src\Inventor\Win\engines\SoGuiEngines.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\Engines.h.in:src\Inventor\Win\engines\SoGuiEngines.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\engines\SoGuiEngines.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\Engines.h.in:src\Inventor\Win\engines\SoGuiEngines.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\engines\SoGuiEngines.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\Engines.h.in:src\Inventor\Win\engines\SoGuiEngines.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\engines\SoGuiEngines.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\Engines.h.in:src\Inventor\Win\engines\SoGuiEngines.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\engines\Format.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\engines\Format.h.in

"src\Inventor\Win\engines\SoGuiFormat.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\Format.h.in:src\Inventor\Win\engines\SoGuiFormat.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\engines\SoGuiFormat.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\Format.h.in:src\Inventor\Win\engines\SoGuiFormat.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\engines\SoGuiFormat.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\Format.h.in:src\Inventor\Win\engines\SoGuiFormat.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\engines\SoGuiFormat.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\Format.h.in:src\Inventor\Win\engines\SoGuiFormat.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\engines\RadioGroup.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\engines\RadioGroup.h.in

"src\Inventor\Win\engines\SoGuiRadioGroup.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\RadioGroup.h.in:src\Inventor\Win\engines\SoGuiRadioGroup.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\engines\SoGuiRadioGroup.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\RadioGroup.h.in:src\Inventor\Win\engines\SoGuiRadioGroup.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\engines\SoGuiRadioGroup.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\RadioGroup.h.in:src\Inventor\Win\engines\SoGuiRadioGroup.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\engines\SoGuiRadioGroup.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\engines\RadioGroup.h.in:src\Inventor\Win\engines\SoGuiRadioGroup.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\ClickCounter.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\ClickCounter.cpp.in

"src\Inventor\Win\nodes\ClickCounter.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ClickCounter.cpp.in:src\Inventor\Win\nodes\ClickCounter.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\ClickCounter.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ClickCounter.cpp.in:src\Inventor\Win\nodes\ClickCounter.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\ClickCounter.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ClickCounter.cpp.in:src\Inventor\Win\nodes\ClickCounter.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\ClickCounter.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ClickCounter.cpp.in:src\Inventor\Win\nodes\ClickCounter.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\ColorEditor.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\ColorEditor.cpp.in

"src\Inventor\Win\nodes\ColorEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ColorEditor.cpp.in:src\Inventor\Win\nodes\ColorEditor.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\ColorEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ColorEditor.cpp.in:src\Inventor\Win\nodes\ColorEditor.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\ColorEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ColorEditor.cpp.in:src\Inventor\Win\nodes\ColorEditor.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\ColorEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ColorEditor.cpp.in:src\Inventor\Win\nodes\ColorEditor.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\Frame.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\Frame.cpp.in

"src\Inventor\Win\nodes\Frame.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Frame.cpp.in:src\Inventor\Win\nodes\Frame.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Frame.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Frame.cpp.in:src\Inventor\Win\nodes\Frame.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Frame.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Frame.cpp.in:src\Inventor\Win\nodes\Frame.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Frame.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Frame.cpp.in:src\Inventor\Win\nodes\Frame.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\Image.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\Image.cpp.in

"src\Inventor\Win\nodes\Image.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Image.cpp.in:src\Inventor\Win\nodes\Image.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Image.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Image.cpp.in:src\Inventor\Win\nodes\Image.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Image.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Image.cpp.in:src\Inventor\Win\nodes\Image.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Image.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Image.cpp.in:src\Inventor\Win\nodes\Image.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\Label.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\Label.cpp.in

"src\Inventor\Win\nodes\Label.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Label.cpp.in:src\Inventor\Win\nodes\Label.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Label.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Label.cpp.in:src\Inventor\Win\nodes\Label.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Label.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Label.cpp.in:src\Inventor\Win\nodes\Label.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Label.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Label.cpp.in:src\Inventor\Win\nodes\Label.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\MaterialEditor.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\MaterialEditor.cpp.in

"src\Inventor\Win\nodes\MaterialEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\MaterialEditor.cpp.in:src\Inventor\Win\nodes\MaterialEditor.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\MaterialEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\MaterialEditor.cpp.in:src\Inventor\Win\nodes\MaterialEditor.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\MaterialEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\MaterialEditor.cpp.in:src\Inventor\Win\nodes\MaterialEditor.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\MaterialEditor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\MaterialEditor.cpp.in:src\Inventor\Win\nodes\MaterialEditor.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\Nodes.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\Nodes.cpp.in

"src\Inventor\Win\nodes\Nodes.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Nodes.cpp.in:src\Inventor\Win\nodes\Nodes.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Nodes.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Nodes.cpp.in:src\Inventor\Win\nodes\Nodes.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Nodes.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Nodes.cpp.in:src\Inventor\Win\nodes\Nodes.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Nodes.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Nodes.cpp.in:src\Inventor\Win\nodes\Nodes.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\Pane.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\Pane.cpp.in

"src\Inventor\Win\nodes\Pane.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Pane.cpp.in:src\Inventor\Win\nodes\Pane.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Pane.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Pane.cpp.in:src\Inventor\Win\nodes\Pane.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Pane.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Pane.cpp.in:src\Inventor\Win\nodes\Pane.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Pane.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Pane.cpp.in:src\Inventor\Win\nodes\Pane.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\Position.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\Position.cpp.in

"src\Inventor\Win\nodes\Position.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Position.cpp.in:src\Inventor\Win\nodes\Position.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Position.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Position.cpp.in:src\Inventor\Win\nodes\Position.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Position.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Position.cpp.in:src\Inventor\Win\nodes\Position.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Position.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Position.cpp.in:src\Inventor\Win\nodes\Position.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\RadioButton.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\RadioButton.cpp.in

"src\Inventor\Win\nodes\RadioButton.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\RadioButton.cpp.in:src\Inventor\Win\nodes\RadioButton.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\RadioButton.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\RadioButton.cpp.in:src\Inventor\Win\nodes\RadioButton.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\RadioButton.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\RadioButton.cpp.in:src\Inventor\Win\nodes\RadioButton.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\RadioButton.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\RadioButton.cpp.in:src\Inventor\Win\nodes\RadioButton.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\SceneTexture2.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\SceneTexture2.cpp.in

"src\Inventor\Win\nodes\SceneTexture2.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\SceneTexture2.cpp.in:src\Inventor\Win\nodes\SceneTexture2.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SceneTexture2.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\SceneTexture2.cpp.in:src\Inventor\Win\nodes\SceneTexture2.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SceneTexture2.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\SceneTexture2.cpp.in:src\Inventor\Win\nodes\SceneTexture2.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SceneTexture2.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\SceneTexture2.cpp.in:src\Inventor\Win\nodes\SceneTexture2.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\Slider1.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\Slider1.cpp.in

"src\Inventor\Win\nodes\Slider1.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Slider1.cpp.in:src\Inventor\Win\nodes\Slider1.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Slider1.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Slider1.cpp.in:src\Inventor\Win\nodes\Slider1.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Slider1.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Slider1.cpp.in:src\Inventor\Win\nodes\Slider1.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Slider1.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Slider1.cpp.in:src\Inventor\Win\nodes\Slider1.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\Slider2.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\Slider2.cpp.in

"src\Inventor\Win\nodes\Slider2.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Slider2.cpp.in:src\Inventor\Win\nodes\Slider2.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Slider2.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Slider2.cpp.in:src\Inventor\Win\nodes\Slider2.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Slider2.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Slider2.cpp.in:src\Inventor\Win\nodes\Slider2.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Slider2.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Slider2.cpp.in:src\Inventor\Win\nodes\Slider2.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\ClickCounter.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\ClickCounter.h.in

"src\Inventor\Win\nodes\SoGuiClickCounter.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ClickCounter.h.in:src\Inventor\Win\nodes\SoGuiClickCounter.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiClickCounter.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ClickCounter.h.in:src\Inventor\Win\nodes\SoGuiClickCounter.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiClickCounter.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ClickCounter.h.in:src\Inventor\Win\nodes\SoGuiClickCounter.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiClickCounter.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ClickCounter.h.in:src\Inventor\Win\nodes\SoGuiClickCounter.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\ColorEditor.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\ColorEditor.h.in

"src\Inventor\Win\nodes\SoGuiColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ColorEditor.h.in:src\Inventor\Win\nodes\SoGuiColorEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ColorEditor.h.in:src\Inventor\Win\nodes\SoGuiColorEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ColorEditor.h.in:src\Inventor\Win\nodes\SoGuiColorEditor.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ColorEditor.h.in:src\Inventor\Win\nodes\SoGuiColorEditor.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\Frame.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\Frame.h.in

"src\Inventor\Win\nodes\SoGuiFrame.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Frame.h.in:src\Inventor\Win\nodes\SoGuiFrame.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiFrame.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Frame.h.in:src\Inventor\Win\nodes\SoGuiFrame.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiFrame.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Frame.h.in:src\Inventor\Win\nodes\SoGuiFrame.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiFrame.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Frame.h.in:src\Inventor\Win\nodes\SoGuiFrame.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\Image.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\Image.h.in

"src\Inventor\Win\nodes\SoGuiImage.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Image.h.in:src\Inventor\Win\nodes\SoGuiImage.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiImage.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Image.h.in:src\Inventor\Win\nodes\SoGuiImage.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiImage.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Image.h.in:src\Inventor\Win\nodes\SoGuiImage.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiImage.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Image.h.in:src\Inventor\Win\nodes\SoGuiImage.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\Label.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\Label.h.in

"src\Inventor\Win\nodes\SoGuiLabel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Label.h.in:src\Inventor\Win\nodes\SoGuiLabel.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiLabel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Label.h.in:src\Inventor\Win\nodes\SoGuiLabel.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiLabel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Label.h.in:src\Inventor\Win\nodes\SoGuiLabel.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiLabel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Label.h.in:src\Inventor\Win\nodes\SoGuiLabel.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\MaterialEditor.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\MaterialEditor.h.in

"src\Inventor\Win\nodes\SoGuiMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\MaterialEditor.h.in:src\Inventor\Win\nodes\SoGuiMaterialEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\MaterialEditor.h.in:src\Inventor\Win\nodes\SoGuiMaterialEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\MaterialEditor.h.in:src\Inventor\Win\nodes\SoGuiMaterialEditor.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\MaterialEditor.h.in:src\Inventor\Win\nodes\SoGuiMaterialEditor.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\Nodes.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\Nodes.h.in

"src\Inventor\Win\nodes\SoGuiNodes.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Nodes.h.in:src\Inventor\Win\nodes\SoGuiNodes.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiNodes.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Nodes.h.in:src\Inventor\Win\nodes\SoGuiNodes.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiNodes.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Nodes.h.in:src\Inventor\Win\nodes\SoGuiNodes.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiNodes.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Nodes.h.in:src\Inventor\Win\nodes\SoGuiNodes.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\Pane.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\Pane.h.in

"src\Inventor\Win\nodes\SoGuiPane.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Pane.h.in:src\Inventor\Win\nodes\SoGuiPane.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiPane.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Pane.h.in:src\Inventor\Win\nodes\SoGuiPane.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiPane.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Pane.h.in:src\Inventor\Win\nodes\SoGuiPane.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiPane.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Pane.h.in:src\Inventor\Win\nodes\SoGuiPane.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\Position.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\Position.h.in

"src\Inventor\Win\nodes\SoGuiPosition.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Position.h.in:src\Inventor\Win\nodes\SoGuiPosition.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiPosition.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Position.h.in:src\Inventor\Win\nodes\SoGuiPosition.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiPosition.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Position.h.in:src\Inventor\Win\nodes\SoGuiPosition.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiPosition.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Position.h.in:src\Inventor\Win\nodes\SoGuiPosition.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\RadioButton.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\RadioButton.h.in

"src\Inventor\Win\nodes\SoGuiRadioButton.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\RadioButton.h.in:src\Inventor\Win\nodes\SoGuiRadioButton.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiRadioButton.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\RadioButton.h.in:src\Inventor\Win\nodes\SoGuiRadioButton.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiRadioButton.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\RadioButton.h.in:src\Inventor\Win\nodes\SoGuiRadioButton.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiRadioButton.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\RadioButton.h.in:src\Inventor\Win\nodes\SoGuiRadioButton.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\SceneTexture2.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\SceneTexture2.h.in

"src\Inventor\Win\nodes\SoGuiSceneTexture2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\SceneTexture2.h.in:src\Inventor\Win\nodes\SoGuiSceneTexture2.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiSceneTexture2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\SceneTexture2.h.in:src\Inventor\Win\nodes\SoGuiSceneTexture2.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiSceneTexture2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\SceneTexture2.h.in:src\Inventor\Win\nodes\SoGuiSceneTexture2.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiSceneTexture2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\SceneTexture2.h.in:src\Inventor\Win\nodes\SoGuiSceneTexture2.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\Slider1.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\Slider1.h.in

"src\Inventor\Win\nodes\SoGuiSlider1.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Slider1.h.in:src\Inventor\Win\nodes\SoGuiSlider1.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiSlider1.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Slider1.h.in:src\Inventor\Win\nodes\SoGuiSlider1.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiSlider1.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Slider1.h.in:src\Inventor\Win\nodes\SoGuiSlider1.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiSlider1.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Slider1.h.in:src\Inventor\Win\nodes\SoGuiSlider1.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\Slider2.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\Slider2.h.in

"src\Inventor\Win\nodes\SoGuiSlider2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Slider2.h.in:src\Inventor\Win\nodes\SoGuiSlider2.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiSlider2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Slider2.h.in:src\Inventor\Win\nodes\SoGuiSlider2.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiSlider2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Slider2.h.in:src\Inventor\Win\nodes\SoGuiSlider2.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiSlider2.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Slider2.h.in:src\Inventor\Win\nodes\SoGuiSlider2.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\ToggleButton.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\ToggleButton.h.in

"src\Inventor\Win\nodes\SoGuiToggleButton.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ToggleButton.h.in:src\Inventor\Win\nodes\SoGuiToggleButton.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiToggleButton.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ToggleButton.h.in:src\Inventor\Win\nodes\SoGuiToggleButton.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiToggleButton.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ToggleButton.h.in:src\Inventor\Win\nodes\SoGuiToggleButton.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiToggleButton.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ToggleButton.h.in:src\Inventor\Win\nodes\SoGuiToggleButton.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\Translation.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\Translation.h.in

"src\Inventor\Win\nodes\SoGuiTranslation.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Translation.h.in:src\Inventor\Win\nodes\SoGuiTranslation.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiTranslation.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Translation.h.in:src\Inventor\Win\nodes\SoGuiTranslation.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiTranslation.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Translation.h.in:src\Inventor\Win\nodes\SoGuiTranslation.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiTranslation.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Translation.h.in:src\Inventor\Win\nodes\SoGuiTranslation.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\ViewpointWrapper.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\ViewpointWrapper.h.in

"src\Inventor\Win\nodes\SoGuiViewpointWrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ViewpointWrapper.h.in:src\Inventor\Win\nodes\SoGuiViewpointWrapper.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiViewpointWrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ViewpointWrapper.h.in:src\Inventor\Win\nodes\SoGuiViewpointWrapper.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiViewpointWrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ViewpointWrapper.h.in:src\Inventor\Win\nodes\SoGuiViewpointWrapper.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiViewpointWrapper.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ViewpointWrapper.h.in:src\Inventor\Win\nodes\SoGuiViewpointWrapper.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\ViewportFix.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\ViewportFix.h.in

"src\Inventor\Win\nodes\SoGuiViewportFix.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ViewportFix.h.in:src\Inventor\Win\nodes\SoGuiViewportFix.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiViewportFix.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ViewportFix.h.in:src\Inventor\Win\nodes\SoGuiViewportFix.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiViewportFix.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ViewportFix.h.in:src\Inventor\Win\nodes\SoGuiViewportFix.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\SoGuiViewportFix.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ViewportFix.h.in:src\Inventor\Win\nodes\SoGuiViewportFix.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\ToggleButton.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\ToggleButton.cpp.in

"src\Inventor\Win\nodes\ToggleButton.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ToggleButton.cpp.in:src\Inventor\Win\nodes\ToggleButton.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\ToggleButton.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ToggleButton.cpp.in:src\Inventor\Win\nodes\ToggleButton.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\ToggleButton.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ToggleButton.cpp.in:src\Inventor\Win\nodes\ToggleButton.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\ToggleButton.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ToggleButton.cpp.in:src\Inventor\Win\nodes\ToggleButton.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\Translation.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\Translation.cpp.in

"src\Inventor\Win\nodes\Translation.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Translation.cpp.in:src\Inventor\Win\nodes\Translation.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Translation.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Translation.cpp.in:src\Inventor\Win\nodes\Translation.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Translation.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Translation.cpp.in:src\Inventor\Win\nodes\Translation.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\Translation.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\Translation.cpp.in:src\Inventor\Win\nodes\Translation.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\ViewpointWrapper.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\ViewpointWrapper.cpp.in

"src\Inventor\Win\nodes\ViewpointWrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ViewpointWrapper.cpp.in:src\Inventor\Win\nodes\ViewpointWrapper.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\ViewpointWrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ViewpointWrapper.cpp.in:src\Inventor\Win\nodes\ViewpointWrapper.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\ViewpointWrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ViewpointWrapper.cpp.in:src\Inventor\Win\nodes\ViewpointWrapper.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\ViewpointWrapper.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ViewpointWrapper.cpp.in:src\Inventor\Win\nodes\ViewpointWrapper.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\nodes\ViewportFix.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\nodes\ViewportFix.cpp.in

"src\Inventor\Win\nodes\ViewportFix.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ViewportFix.cpp.in:src\Inventor\Win\nodes\ViewportFix.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\ViewportFix.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ViewportFix.cpp.in:src\Inventor\Win\nodes\ViewportFix.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\ViewportFix.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ViewportFix.cpp.in:src\Inventor\Win\nodes\ViewportFix.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\nodes\ViewportFix.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\nodes\ViewportFix.cpp.in:src\Inventor\Win\nodes\ViewportFix.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\SoAny.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\SoAny.cpp.in

"src\Inventor\Win\SoAny.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoAny.cpp.in:src\Inventor\Win\SoAny.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoAny.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoAny.cpp.in:src\Inventor\Win\SoAny.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoAny.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoAny.cpp.in:src\Inventor\Win\SoAny.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoAny.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoAny.cpp.in:src\Inventor\Win\SoAny.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\SoAny.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\SoAny.h.in

"src\Inventor\Win\SoAny.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoAny.h.in:src\Inventor\Win\SoAny.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoAny.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoAny.h.in:src\Inventor\Win\SoAny.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoAny.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoAny.h.in:src\Inventor\Win\SoAny.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoAny.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoAny.h.in:src\Inventor\Win\SoAny.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\SoGuiComponentP.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\SoGuiComponentP.h.in

"src\Inventor\Win\SoGuiComponentP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiComponentP.h.in:src\Inventor\Win\SoGuiComponentP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoGuiComponentP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiComponentP.h.in:src\Inventor\Win\SoGuiComponentP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoGuiComponentP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiComponentP.h.in:src\Inventor\Win\SoGuiComponentP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoGuiComponentP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiComponentP.h.in:src\Inventor\Win\SoGuiComponentP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\SoGuiGLWidgetP.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\SoGuiGLWidgetP.h.in

"src\Inventor\Win\SoGuiGLWidgetP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiGLWidgetP.h.in:src\Inventor\Win\SoGuiGLWidgetP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoGuiGLWidgetP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiGLWidgetP.h.in:src\Inventor\Win\SoGuiGLWidgetP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoGuiGLWidgetP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiGLWidgetP.h.in:src\Inventor\Win\SoGuiGLWidgetP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoGuiGLWidgetP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiGLWidgetP.h.in:src\Inventor\Win\SoGuiGLWidgetP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\SoGuiP.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\SoGuiP.h.in

"src\Inventor\Win\SoGuiP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiP.h.in:src\Inventor\Win\SoGuiP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoGuiP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiP.h.in:src\Inventor\Win\SoGuiP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoGuiP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiP.h.in:src\Inventor\Win\SoGuiP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoGuiP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiP.h.in:src\Inventor\Win\SoGuiP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\SoGui.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\SoGui.h.in

"src\Inventor\Win\SoWin.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGui.h.in:src\Inventor\Win\SoWin.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWin.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGui.h.in:src\Inventor\Win\SoWin.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWin.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGui.h.in:src\Inventor\Win\SoWin.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWin.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGui.h.in:src\Inventor\Win\SoWin.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\editors\SoGuiColorEditor.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\editors\SoGuiColorEditor.h.in

"src\Inventor\Win\SoWinColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiColorEditor.h.in:src\Inventor\Win\SoWinColorEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiColorEditor.h.in:src\Inventor\Win\SoWinColorEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiColorEditor.h.in:src\Inventor\Win\SoWinColorEditor.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinColorEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiColorEditor.h.in:src\Inventor\Win\SoWinColorEditor.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\SoGuiCommon.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\SoGuiCommon.cpp.in

"src\Inventor\Win\SoWinCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiCommon.cpp.in:src\Inventor\Win\SoWinCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiCommon.cpp.in:src\Inventor\Win\SoWinCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiCommon.cpp.in:src\Inventor\Win\SoWinCommon.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiCommon.cpp.in:src\Inventor\Win\SoWinCommon.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\SoGuiComponent.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\SoGuiComponent.h.in

"src\Inventor\Win\SoWinComponent.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiComponent.h.in:src\Inventor\Win\SoWinComponent.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinComponent.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiComponent.h.in:src\Inventor\Win\SoWinComponent.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinComponent.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiComponent.h.in:src\Inventor\Win\SoWinComponent.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinComponent.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiComponent.h.in:src\Inventor\Win\SoWinComponent.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\SoGuiComponentCommon.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\SoGuiComponentCommon.cpp.in

"src\Inventor\Win\SoWinComponentCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiComponentCommon.cpp.in:src\Inventor\Win\SoWinComponentCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinComponentCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiComponentCommon.cpp.in:src\Inventor\Win\SoWinComponentCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinComponentCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiComponentCommon.cpp.in:src\Inventor\Win\SoWinComponentCommon.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinComponentCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiComponentCommon.cpp.in:src\Inventor\Win\SoWinComponentCommon.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\SoGuiCursor.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\SoGuiCursor.cpp.in

"src\Inventor\Win\SoWinCursor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiCursor.cpp.in:src\Inventor\Win\SoWinCursor.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinCursor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiCursor.cpp.in:src\Inventor\Win\SoWinCursor.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinCursor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiCursor.cpp.in:src\Inventor\Win\SoWinCursor.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinCursor.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiCursor.cpp.in:src\Inventor\Win\SoWinCursor.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\SoGuiCursor.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\SoGuiCursor.h.in

"src\Inventor\Win\SoWinCursor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiCursor.h.in:src\Inventor\Win\SoWinCursor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinCursor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiCursor.h.in:src\Inventor\Win\SoWinCursor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinCursor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiCursor.h.in:src\Inventor\Win\SoWinCursor.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinCursor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiCursor.h.in:src\Inventor\Win\SoWinCursor.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\SoGuiGLWidget.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\SoGuiGLWidget.h.in

"src\Inventor\Win\SoWinGLWidget.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiGLWidget.h.in:src\Inventor\Win\SoWinGLWidget.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinGLWidget.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiGLWidget.h.in:src\Inventor\Win\SoWinGLWidget.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinGLWidget.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiGLWidget.h.in:src\Inventor\Win\SoWinGLWidget.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinGLWidget.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiGLWidget.h.in:src\Inventor\Win\SoWinGLWidget.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\SoGuiGLWidgetCommon.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\SoGuiGLWidgetCommon.cpp.in

"src\Inventor\Win\SoWinGLWidgetCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiGLWidgetCommon.cpp.in:src\Inventor\Win\SoWinGLWidgetCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinGLWidgetCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiGLWidgetCommon.cpp.in:src\Inventor\Win\SoWinGLWidgetCommon.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinGLWidgetCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiGLWidgetCommon.cpp.in:src\Inventor\Win\SoWinGLWidgetCommon.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinGLWidgetCommon.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiGLWidgetCommon.cpp.in:src\Inventor\Win\SoWinGLWidgetCommon.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\editors\SoGuiMaterialEditor.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\editors\SoGuiMaterialEditor.h.in

"src\Inventor\Win\SoWinMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiMaterialEditor.h.in:src\Inventor\Win\SoWinMaterialEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiMaterialEditor.h.in:src\Inventor\Win\SoWinMaterialEditor.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiMaterialEditor.h.in:src\Inventor\Win\SoWinMaterialEditor.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinMaterialEditor.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\editors\SoGuiMaterialEditor.h.in:src\Inventor\Win\SoWinMaterialEditor.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\SoGuiObject.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\SoGuiObject.cpp.in

"src\Inventor\Win\SoWinObject.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiObject.cpp.in:src\Inventor\Win\SoWinObject.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinObject.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiObject.cpp.in:src\Inventor\Win\SoWinObject.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinObject.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiObject.cpp.in:src\Inventor\Win\SoWinObject.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinObject.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiObject.cpp.in:src\Inventor\Win\SoWinObject.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\SoGuiObject.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\SoGuiObject.h.in

"src\Inventor\Win\SoWinObject.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiObject.h.in:src\Inventor\Win\SoWinObject.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinObject.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiObject.h.in:src\Inventor\Win\SoWinObject.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinObject.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiObject.h.in:src\Inventor\Win\SoWinObject.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinObject.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiObject.h.in:src\Inventor\Win\SoWinObject.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\SoGuiRenderArea.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\SoGuiRenderArea.cpp.in

"src\Inventor\Win\SoWinRenderArea.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiRenderArea.cpp.in:src\Inventor\Win\SoWinRenderArea.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinRenderArea.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiRenderArea.cpp.in:src\Inventor\Win\SoWinRenderArea.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinRenderArea.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiRenderArea.cpp.in:src\Inventor\Win\SoWinRenderArea.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinRenderArea.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiRenderArea.cpp.in:src\Inventor\Win\SoWinRenderArea.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\SoGuiRenderArea.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\SoGuiRenderArea.h.in

"src\Inventor\Win\SoWinRenderArea.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiRenderArea.h.in:src\Inventor\Win\SoWinRenderArea.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinRenderArea.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiRenderArea.h.in:src\Inventor\Win\SoWinRenderArea.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinRenderArea.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiRenderArea.h.in:src\Inventor\Win\SoWinRenderArea.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\SoWinRenderArea.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\SoGuiRenderArea.h.in:src\Inventor\Win\SoWinRenderArea.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\viewers\SoGuiExaminerViewerP.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\viewers\SoGuiExaminerViewerP.h.in

"src\Inventor\Win\viewers\SoGuiExaminerViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiExaminerViewerP.h.in:src\Inventor\Win\viewers\SoGuiExaminerViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoGuiExaminerViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiExaminerViewerP.h.in:src\Inventor\Win\viewers\SoGuiExaminerViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoGuiExaminerViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiExaminerViewerP.h.in:src\Inventor\Win\viewers\SoGuiExaminerViewerP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoGuiExaminerViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiExaminerViewerP.h.in:src\Inventor\Win\viewers\SoGuiExaminerViewerP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\viewers\SoGuiFullViewerP.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\viewers\SoGuiFullViewerP.h.in

"src\Inventor\Win\viewers\SoGuiFullViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiFullViewerP.h.in:src\Inventor\Win\viewers\SoGuiFullViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoGuiFullViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiFullViewerP.h.in:src\Inventor\Win\viewers\SoGuiFullViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoGuiFullViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiFullViewerP.h.in:src\Inventor\Win\viewers\SoGuiFullViewerP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoGuiFullViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiFullViewerP.h.in:src\Inventor\Win\viewers\SoGuiFullViewerP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\viewers\SoGuiPlaneViewerP.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\viewers\SoGuiPlaneViewerP.h.in

"src\Inventor\Win\viewers\SoGuiPlaneViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiPlaneViewerP.h.in:src\Inventor\Win\viewers\SoGuiPlaneViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoGuiPlaneViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiPlaneViewerP.h.in:src\Inventor\Win\viewers\SoGuiPlaneViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoGuiPlaneViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiPlaneViewerP.h.in:src\Inventor\Win\viewers\SoGuiPlaneViewerP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoGuiPlaneViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiPlaneViewerP.h.in:src\Inventor\Win\viewers\SoGuiPlaneViewerP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\viewers\SoGuiViewerP.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\viewers\SoGuiViewerP.h.in

"src\Inventor\Win\viewers\SoGuiViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiViewerP.h.in:src\Inventor\Win\viewers\SoGuiViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoGuiViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiViewerP.h.in:src\Inventor\Win\viewers\SoGuiViewerP.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoGuiViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiViewerP.h.in:src\Inventor\Win\viewers\SoGuiViewerP.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoGuiViewerP.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiViewerP.h.in:src\Inventor\Win\viewers\SoGuiViewerP.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\viewers\SoGuiConstrainedViewer.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\viewers\SoGuiConstrainedViewer.cpp.in

"src\Inventor\Win\viewers\SoWinConstrainedViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiConstrainedViewer.cpp.in:src\Inventor\Win\viewers\SoWinConstrainedViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinConstrainedViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiConstrainedViewer.cpp.in:src\Inventor\Win\viewers\SoWinConstrainedViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinConstrainedViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiConstrainedViewer.cpp.in:src\Inventor\Win\viewers\SoWinConstrainedViewer.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinConstrainedViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiConstrainedViewer.cpp.in:src\Inventor\Win\viewers\SoWinConstrainedViewer.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\viewers\SoGuiConstrainedViewer.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\viewers\SoGuiConstrainedViewer.h.in

"src\Inventor\Win\viewers\SoWinConstrainedViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiConstrainedViewer.h.in:src\Inventor\Win\viewers\SoWinConstrainedViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinConstrainedViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiConstrainedViewer.h.in:src\Inventor\Win\viewers\SoWinConstrainedViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinConstrainedViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiConstrainedViewer.h.in:src\Inventor\Win\viewers\SoWinConstrainedViewer.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinConstrainedViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiConstrainedViewer.h.in:src\Inventor\Win\viewers\SoWinConstrainedViewer.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\viewers\SoGuiExaminerViewer.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\viewers\SoGuiExaminerViewer.cpp.in

"src\Inventor\Win\viewers\SoWinExaminerViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiExaminerViewer.cpp.in:src\Inventor\Win\viewers\SoWinExaminerViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinExaminerViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiExaminerViewer.cpp.in:src\Inventor\Win\viewers\SoWinExaminerViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinExaminerViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiExaminerViewer.cpp.in:src\Inventor\Win\viewers\SoWinExaminerViewer.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinExaminerViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiExaminerViewer.cpp.in:src\Inventor\Win\viewers\SoWinExaminerViewer.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\viewers\SoGuiExaminerViewer.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\viewers\SoGuiExaminerViewer.h.in

"src\Inventor\Win\viewers\SoWinExaminerViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiExaminerViewer.h.in:src\Inventor\Win\viewers\SoWinExaminerViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinExaminerViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiExaminerViewer.h.in:src\Inventor\Win\viewers\SoWinExaminerViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinExaminerViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiExaminerViewer.h.in:src\Inventor\Win\viewers\SoWinExaminerViewer.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinExaminerViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiExaminerViewer.h.in:src\Inventor\Win\viewers\SoWinExaminerViewer.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\viewers\SoGuiFlyViewer.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\viewers\SoGuiFlyViewer.cpp.in

"src\Inventor\Win\viewers\SoWinFlyViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiFlyViewer.cpp.in:src\Inventor\Win\viewers\SoWinFlyViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinFlyViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiFlyViewer.cpp.in:src\Inventor\Win\viewers\SoWinFlyViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinFlyViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiFlyViewer.cpp.in:src\Inventor\Win\viewers\SoWinFlyViewer.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinFlyViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiFlyViewer.cpp.in:src\Inventor\Win\viewers\SoWinFlyViewer.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\viewers\SoGuiFlyViewer.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\viewers\SoGuiFlyViewer.h.in

"src\Inventor\Win\viewers\SoWinFlyViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiFlyViewer.h.in:src\Inventor\Win\viewers\SoWinFlyViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinFlyViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiFlyViewer.h.in:src\Inventor\Win\viewers\SoWinFlyViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinFlyViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiFlyViewer.h.in:src\Inventor\Win\viewers\SoWinFlyViewer.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinFlyViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiFlyViewer.h.in:src\Inventor\Win\viewers\SoWinFlyViewer.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\viewers\SoGuiFullViewer.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\viewers\SoGuiFullViewer.cpp.in

"src\Inventor\Win\viewers\SoWinFullViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiFullViewer.cpp.in:src\Inventor\Win\viewers\SoWinFullViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinFullViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiFullViewer.cpp.in:src\Inventor\Win\viewers\SoWinFullViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinFullViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiFullViewer.cpp.in:src\Inventor\Win\viewers\SoWinFullViewer.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinFullViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiFullViewer.cpp.in:src\Inventor\Win\viewers\SoWinFullViewer.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\viewers\SoGuiFullViewer.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\viewers\SoGuiFullViewer.h.in

"src\Inventor\Win\viewers\SoWinFullViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiFullViewer.h.in:src\Inventor\Win\viewers\SoWinFullViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinFullViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiFullViewer.h.in:src\Inventor\Win\viewers\SoWinFullViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinFullViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiFullViewer.h.in:src\Inventor\Win\viewers\SoWinFullViewer.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinFullViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiFullViewer.h.in:src\Inventor\Win\viewers\SoWinFullViewer.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\viewers\SoGuiPlaneViewer.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\viewers\SoGuiPlaneViewer.cpp.in

"src\Inventor\Win\viewers\SoWinPlaneViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiPlaneViewer.cpp.in:src\Inventor\Win\viewers\SoWinPlaneViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinPlaneViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiPlaneViewer.cpp.in:src\Inventor\Win\viewers\SoWinPlaneViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinPlaneViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiPlaneViewer.cpp.in:src\Inventor\Win\viewers\SoWinPlaneViewer.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinPlaneViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiPlaneViewer.cpp.in:src\Inventor\Win\viewers\SoWinPlaneViewer.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\viewers\SoGuiPlaneViewer.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\viewers\SoGuiPlaneViewer.h.in

"src\Inventor\Win\viewers\SoWinPlaneViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiPlaneViewer.h.in:src\Inventor\Win\viewers\SoWinPlaneViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinPlaneViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiPlaneViewer.h.in:src\Inventor\Win\viewers\SoWinPlaneViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinPlaneViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiPlaneViewer.h.in:src\Inventor\Win\viewers\SoWinPlaneViewer.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinPlaneViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiPlaneViewer.h.in:src\Inventor\Win\viewers\SoWinPlaneViewer.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\viewers\SoGuiViewer.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\viewers\SoGuiViewer.cpp.in

"src\Inventor\Win\viewers\SoWinViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiViewer.cpp.in:src\Inventor\Win\viewers\SoWinViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiViewer.cpp.in:src\Inventor\Win\viewers\SoWinViewer.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiViewer.cpp.in:src\Inventor\Win\viewers\SoWinViewer.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinViewer.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiViewer.cpp.in:src\Inventor\Win\viewers\SoWinViewer.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\viewers\SoGuiViewer.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\viewers\SoGuiViewer.h.in

"src\Inventor\Win\viewers\SoWinViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiViewer.h.in:src\Inventor\Win\viewers\SoWinViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiViewer.h.in:src\Inventor\Win\viewers\SoWinViewer.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiViewer.h.in:src\Inventor\Win\viewers\SoWinViewer.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\viewers\SoWinViewer.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\viewers\SoGuiViewer.h.in:src\Inventor\Win\viewers\SoWinViewer.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\widgets\SoAnyThumbWheel.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\widgets\SoAnyThumbWheel.cpp.in

"src\Inventor\Win\widgets\SoAnyThumbWheel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\widgets\SoAnyThumbWheel.cpp.in:src\Inventor\Win\widgets\SoAnyThumbWheel.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\widgets\SoAnyThumbWheel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\widgets\SoAnyThumbWheel.cpp.in:src\Inventor\Win\widgets\SoAnyThumbWheel.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\widgets\SoAnyThumbWheel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\widgets\SoAnyThumbWheel.cpp.in:src\Inventor\Win\widgets\SoAnyThumbWheel.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\widgets\SoAnyThumbWheel.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\widgets\SoAnyThumbWheel.cpp.in:src\Inventor\Win\widgets\SoAnyThumbWheel.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\widgets\SoAnyThumbWheel.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\widgets\SoAnyThumbWheel.h.in

"src\Inventor\Win\widgets\SoAnyThumbWheel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\widgets\SoAnyThumbWheel.h.in:src\Inventor\Win\widgets\SoAnyThumbWheel.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\widgets\SoAnyThumbWheel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\widgets\SoAnyThumbWheel.h.in:src\Inventor\Win\widgets\SoAnyThumbWheel.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\widgets\SoAnyThumbWheel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\widgets\SoAnyThumbWheel.h.in:src\Inventor\Win\widgets\SoAnyThumbWheel.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\widgets\SoAnyThumbWheel.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\widgets\SoAnyThumbWheel.h.in:src\Inventor\Win\widgets\SoAnyThumbWheel.h

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\widgets\SoGuiPopupMenu.cpp.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\widgets\SoGuiPopupMenu.cpp.in

"src\Inventor\Win\widgets\SoWinPopupMenu.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\widgets\SoGuiPopupMenu.cpp.in:src\Inventor\Win\widgets\SoWinPopupMenu.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\widgets\SoWinPopupMenu.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\widgets\SoGuiPopupMenu.cpp.in:src\Inventor\Win\widgets\SoWinPopupMenu.cpp

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\widgets\SoWinPopupMenu.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\widgets\SoGuiPopupMenu.cpp.in:src\Inventor\Win\widgets\SoWinPopupMenu.cpp

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\widgets\SoWinPopupMenu.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\widgets\SoGuiPopupMenu.cpp.in:src\Inventor\Win\widgets\SoWinPopupMenu.cpp

# End Custom Build

!ENDIF

# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\common\widgets\SoGuiPopupMenu.h.in

!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=..\..\src\Inventor\Win\common\widgets\SoGuiPopupMenu.h.in

"src\Inventor\Win\widgets\SoWinPopupMenu.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\widgets\SoGuiPopupMenu.h.in:src\Inventor\Win\widgets\SoWinPopupMenu.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\widgets\SoWinPopupMenu.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\widgets\SoGuiPopupMenu.h.in:src\Inventor\Win\widgets\SoWinPopupMenu.h

# End Custom Build

!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\widgets\SoWinPopupMenu.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\widgets\SoGuiPopupMenu.h.in:src\Inventor\Win\widgets\SoWinPopupMenu.h

# End Custom Build
  
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"

# PROP IgnoreDefaultTool 1
#Begin Custom Build - subst'ing $(InputPath)
InputPath=

"src\Inventor\Win\widgets\SoWinPopupMenu.h" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	..\..\cfg\csubst --file=..\..\src\Inventor\Win\common\widgets\SoGuiPopupMenu.h.in:src\Inventor\Win\widgets\SoWinPopupMenu.h

# End Custom Build

!ENDIF

# End Source File
# End Group
# Begin Group "Source Files"
# PROP Default_Filter "c;cpp;ic;icc;h"

# Begin Group "Win/devices sources"
# PROP Default_Filter "c;cpp;ic;icc;h"
# Begin Source File

SOURCE=..\..\src\Inventor\Win\devices\SoWinDevice.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\devices\SoWinInputFocus.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\devices\SoWinKeyboard.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\devices\SoWinMouse.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\devices\SoWinSpaceball.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\spwinput_x11.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\spwinput_win32.c
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\SoWinDeviceCommon.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\SoWinInputFocusCommon.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\SoWinKeyboardCommon.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\SoWinMouseCommon.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\devices"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\devices\SoWinSpaceballCommon.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\devices"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\devices"
!ENDIF
# End Source File
# End Group
# Begin Group "Win/editors sources"
# PROP Default_Filter "c;cpp;ic;icc;h"
# Begin Source File

SOURCE=.\src\Inventor\Win\editors\SoWinColorEditor.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\editors"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\editors"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\editors"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\editors"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\editors\SoWinMaterialEditor.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\editors"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\editors"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\editors"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\editors"
!ENDIF
# End Source File
# End Group
# Begin Group "Win/engines sources"
# PROP Default_Filter "c;cpp;ic;icc;h"
# Begin Source File

SOURCE=.\src\Inventor\Win\engines\Engines.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\engines"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\engines"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\engines"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\engines"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\engines\RadioGroup.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\engines"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\engines"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\engines"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\engines"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\engines\Format.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\engines"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\engines"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\engines"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\engines"
!ENDIF
# End Source File
# End Group
# Begin Group "Win/nodes sources"
# PROP Default_Filter "c;cpp;ic;icc;h"
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\Nodes.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\SceneTexture2.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\ViewportFix.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\ViewpointWrapper.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\Pane.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\Position.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\Translation.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\Frame.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\Image.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\Label.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\ToggleButton.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\RadioButton.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\ClickCounter.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\Slider1.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\Slider2.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\ColorEditor.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\nodes"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\nodes\MaterialEditor.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\nodes"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\nodes"
!ENDIF
# End Source File
# End Group
# Begin Group "Win/viewers sources"
# PROP Default_Filter "c;cpp;ic;icc;h"
# Begin Source File

SOURCE=..\..\src\Inventor\Win\viewers\FullViewer.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\viewers"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\viewers\ExaminerViewer.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\viewers"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\viewers\PlaneViewer.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\viewers"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\viewers\SoWinViewer.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\viewers"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\viewers\SoWinConstrainedViewer.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\viewers"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\viewers\SoWinFlyViewer.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\viewers"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\viewers\SoWinFullViewer.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\viewers"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\viewers\SoWinExaminerViewer.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\viewers"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\viewers\SoWinPlaneViewer.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\viewers"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\viewers"
!ENDIF
# End Source File
# End Group
# Begin Group "Win/widgets sources"
# PROP Default_Filter "c;cpp;ic;icc;h"
# Begin Source File

SOURCE=..\..\src\Inventor\Win\widgets\SoWinThumbWheel.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\widgets"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\widgets"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\widgets"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\widgets"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\widgets\WinNativePopupMenu.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\widgets"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\widgets"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\widgets"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\widgets"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\widgets\SoWinBitmapButton.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\widgets"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\widgets"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\widgets"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\widgets"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\widgets\SoAnyThumbWheel.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\widgets"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\widgets"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\widgets"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\widgets"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\widgets\SoWinPopupMenu.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Win\widgets"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Win\widgets"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Win\widgets"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Win\widgets"
!ENDIF
# End Source File
# End Group
# Begin Group "Inventor/Win sources"
# PROP Default_Filter "c;cpp;ic;icc;h"
# Begin Source File

SOURCE=..\..\src\Inventor\Win\SoWin.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Win"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\SoWinComponent.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Win"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\SoWinGLWidget.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Win"
!ENDIF
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\Win32API.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Win"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\SoAny.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Win"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\SoWinCursor.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Win"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\SoWinObject.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Win"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\SoWinCommon.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Win"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\SoWinComponentCommon.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Win"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\SoWinGLWidgetCommon.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Win"
!ENDIF
# End Source File
# Begin Source File

SOURCE=.\src\Inventor\Win\SoWinRenderArea.cpp
!IF  "$(CFG)" == "sowin1 - Win32 DLL (Release)"
# PROP Intermediate_Dir "Release\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 DLL (Debug)"
# PROP Intermediate_Dir "Debug\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Release)"
# PROP Intermediate_Dir "StaticRelease\Inventor\Win"
!ELSEIF  "$(CFG)" == "sowin1 - Win32 LIB (Debug)"
# PROP Intermediate_Dir "StaticDebug\Inventor\Win"
!ENDIF
# End Source File
# End Group
# End Group
# Begin Group "Public Headers"

# PROP Default_Filter "h;ic;icc"
# Begin Group "Inventor\Win\devices headers"
# Set Default_Filter "h"
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
# End Group
# Begin Group "Inventor\Win\editors headers"
# Set Default_Filter "h"
# Begin Source File

SOURCE=src\Inventor\Win\editors\SoWinColorEditor.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\editors\SoWinMaterialEditor.h
# End Source File
# End Group
# Begin Group "Inventor\Win\nodes headers"
# Set Default_Filter "h"
# Begin Source File

SOURCE=src\Inventor\Win\nodes\SoGuiColorEditor.h
# End Source File
# Begin Source File

SOURCE=src\Inventor\Win\nodes\SoGuiMaterialEditor.h
# End Source File
# End Group
# Begin Group "Inventor\Win\viewers headers"
# Set Default_Filter "h"
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
# End Group
# Begin Group "Inventor\Win\widgets headers"
# Set Default_Filter "h"
# Begin Source File

SOURCE=src\Inventor\Win\widgets\SoWinPopupMenu.h
# End Source File
# End Group
# Begin Group "Inventor\Win headers"
# Set Default_Filter "h"
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
# End Group
# Begin Group "Private Headers"

# PROP Default_Filter "h;ic;icc"
# Begin Group "Win local includes"

# PROP Default_Filter "h;ic;icc"
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
# End Group
# Begin Group "devices local includes"

# PROP Default_Filter "h;ic;icc"
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
# End Group
# Begin Group "engines local includes"

# PROP Default_Filter "h;ic;icc"
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
# End Group
# Begin Group "nodes local includes"

# PROP Default_Filter "h;ic;icc"
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
# End Group
# Begin Group "viewers local includes"

# PROP Default_Filter "h;ic;icc"
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

SOURCE=.\src\Inventor\Win\viewers\SoGuiViewerP.h

# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "src local includes"

# PROP Default_Filter "h;ic;icc"
# Begin Source File

SOURCE=.\src\config-debug.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\config-release.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\src\sowindefs.h

# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "Win local includes"

# PROP Default_Filter "h;ic;icc"
# Begin Source File

SOURCE=..\..\src\Inventor\Win\SoWinComponentP.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\SoWinGLWidgetP.h

# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "devices local includes"

# PROP Default_Filter "h;ic;icc"
# Begin Source File

SOURCE=..\..\src\Inventor\Win\devices\SoWinDeviceP.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\devices\SoWinSpaceballP.h

# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "viewers local includes"

# PROP Default_Filter "h;ic;icc"
# Begin Source File

SOURCE=..\..\src\Inventor\Win\viewers\SoWinExaminerViewerP.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\viewers\SoWinFullViewerP.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\viewers\SoWinPlaneViewerP.h

# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "widgets local includes"

# PROP Default_Filter "h;ic;icc"
# Begin Source File

SOURCE=..\..\src\Inventor\Win\widgets\SoWinBitmapButton.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\widgets\SoWinThumbWheel.h

# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=..\..\src\Inventor\Win\widgets\WinNativePopupMenu.h

# PROP Exclude_From_Build 1
# End Source File
# End Group
# End Group
# End Target
# End Project

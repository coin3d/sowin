############################################################################
## Makefile.am

include src/Inventor/Win/common/Makefile.common

############################################################################
##

SUFFIXES = .cpp .h .m4 .in .o .lo .Plo .TPlo

############################################################################
## 

if BUILD_HTMLPAGES
HTMLDIR = html
else
HTMLDIR =
endif

if BUILD_HTMLHELP
HTMLHELPDIR = htmlhelp
else
HTMLHELPDIR =
endif

if BUILD_LIBRARY
# Material editor(s) not part of the public API yet, so there's
# no point yet in installing the material data.
#LIBDIR = data src
LIBDIR = src
else
LIBDIR =
endif

DOCDIRS = man $(HTMLDIR) $(HTMLHELPDIR)

SUBDIRS = . $(LIBDIR) $(DOCDIRS)

BUILT_SOURCES = \
	$(SoGuiAllBuiltFiles)

CLEANFILES = \
	sowin@SOWIN_MAJOR_VERSION@.dsp \
	sowin@SOWIN_MAJOR_VERSION@.dsw \
	$(SoGui_BuiltMetaFiles)

DISTCLEANFILES = \
	libtool \
	$(SoGui_BuiltFiles) \
	$(SoGui_BuiltMetaFiles)

if BUILD_LIBRARY

bin_SCRIPTS = so@gui@-config

m4datadir = $(datadir)/aclocal
# Don't replace "win" with "@gui@" here, it will pukk up
# for ``make dist''.
dist_m4data_DATA = cfg/sowin.m4

cfgdatadir = $(datadir)/Coin/conf
cfgdata_DATA = so@gui@-@CONFIG@.cfg

endif

EXTRA_DIST = \
	LICENSE.GPL \
	cfg/sowin.m4 \
	cfg/gendsp.sh.in \
	cfg/gendsp.pl.in \
	docs/ChangeLog.v1.0.0 \
	docs/ChangeLog.v1.2.0 \
	docs/ChangeLog.v1.3.0 \
	docs/ChangeLog.v1.4.0 \
	docs/announcement-1_1_0.txt \
	docs/announcement-1_2_0.txt \
	docs/announcement-1_3_0.txt \
	docs/announcement-1_4_0.txt \
	packaging/windows/Makefile.in \
	packaging/windows/bfheader.nsi.in \
	packaging/windows/footer.nsi.in \
	packaging/windows/heading.nsi.in \
	packaging/windows/middle.nsi.in \
	packaging/windows/post.nsi.in \
	packaging/windows/sowin-sdk.html.in \
	$(SoGuiCommonDistFiles) \
	build/misc/generate.sh \
	build/misc/install-sdk.bat \
	build/misc/create-directories.bat \
	build/misc/config-wrapper.h \
	build/msvc6/src/Inventor/Win/common/gl.h \
	build/msvc6/src/Inventor/Win/SoAny.cpp \
	build/msvc6/src/Inventor/Win/SoAny.h \
	build/msvc6/src/Inventor/Win/SoGuiComponentP.h \
	build/msvc6/src/Inventor/Win/SoGuiGLWidgetP.h \
	build/msvc6/src/Inventor/Win/SoGuiP.h \
	build/msvc6/src/Inventor/Win/SoWin.h \
	build/msvc6/src/Inventor/Win/SoWinBasic.h \
	build/msvc6/src/Inventor/Win/SoWinColorEditor.h \
	build/msvc6/src/Inventor/Win/SoWinCommon.cpp \
	build/msvc6/src/Inventor/Win/SoWinComponent.h \
	build/msvc6/src/Inventor/Win/SoWinComponentCommon.cpp \
	build/msvc6/src/Inventor/Win/SoWinCursor.cpp \
	build/msvc6/src/Inventor/Win/SoWinCursor.h \
	build/msvc6/src/Inventor/Win/SoWinGLWidget.h \
	build/msvc6/src/Inventor/Win/SoWinGLWidgetCommon.cpp \
	build/msvc6/src/Inventor/Win/SoWinMaterialEditor.h \
	build/msvc6/src/Inventor/Win/SoWinObject.cpp \
	build/msvc6/src/Inventor/Win/SoWinObject.h \
	build/msvc6/src/Inventor/Win/SoWinRenderArea.cpp \
	build/msvc6/src/Inventor/Win/SoWinRenderArea.h \
	build/msvc6/src/Inventor/Win/devices/SoGuiDeviceP.h \
	build/msvc6/src/Inventor/Win/devices/SoGuiInputFocusP.h \
	build/msvc6/src/Inventor/Win/devices/SoGuiKeyboardP.h \
	build/msvc6/src/Inventor/Win/devices/SoGuiMouseP.h \
	build/msvc6/src/Inventor/Win/devices/SoGuiSpaceballP.h \
	build/msvc6/src/Inventor/Win/devices/SoWinDevice.h \
	build/msvc6/src/Inventor/Win/devices/SoWinDeviceCommon.cpp \
	build/msvc6/src/Inventor/Win/devices/SoWinInputFocus.h \
	build/msvc6/src/Inventor/Win/devices/SoWinInputFocusCommon.cpp \
	build/msvc6/src/Inventor/Win/devices/SoWinKeyboard.h \
	build/msvc6/src/Inventor/Win/devices/SoWinKeyboardCommon.cpp \
	build/msvc6/src/Inventor/Win/devices/SoWinMouse.h \
	build/msvc6/src/Inventor/Win/devices/SoWinMouseCommon.cpp \
	build/msvc6/src/Inventor/Win/devices/SoWinSpaceball.h \
	build/msvc6/src/Inventor/Win/devices/SoWinSpaceballCommon.cpp \
	build/msvc6/src/Inventor/Win/devices/spwinput.h \
	build/msvc6/src/Inventor/Win/devices/spwinput_win32.c \
	build/msvc6/src/Inventor/Win/devices/spwinput_win32.h \
	build/msvc6/src/Inventor/Win/devices/spwinput_x11.cpp \
	build/msvc6/src/Inventor/Win/editors/SoWinColorEditor.cpp \
	build/msvc6/src/Inventor/Win/editors/SoWinColorEditor.h \
	build/msvc6/src/Inventor/Win/editors/SoWinMaterialEditor.cpp \
	build/msvc6/src/Inventor/Win/editors/SoWinMaterialEditor.h \
	build/msvc6/src/Inventor/Win/engines/Engines.cpp \
	build/msvc6/src/Inventor/Win/engines/Format.cpp \
	build/msvc6/src/Inventor/Win/engines/RadioGroup.cpp \
	build/msvc6/src/Inventor/Win/engines/SoGuiEngines.h \
	build/msvc6/src/Inventor/Win/engines/SoGuiFormat.h \
	build/msvc6/src/Inventor/Win/engines/SoGuiRadioGroup.h \
	build/msvc6/src/Inventor/Win/nodes/ClickCounter.cpp \
	build/msvc6/src/Inventor/Win/nodes/ColorEditor.cpp \
	build/msvc6/src/Inventor/Win/nodes/Frame.cpp \
	build/msvc6/src/Inventor/Win/nodes/Image.cpp \
	build/msvc6/src/Inventor/Win/nodes/Label.cpp \
	build/msvc6/src/Inventor/Win/nodes/MaterialEditor.cpp \
	build/msvc6/src/Inventor/Win/nodes/Nodes.cpp \
	build/msvc6/src/Inventor/Win/nodes/Pane.cpp \
	build/msvc6/src/Inventor/Win/nodes/Position.cpp \
	build/msvc6/src/Inventor/Win/nodes/RadioButton.cpp \
	build/msvc6/src/Inventor/Win/nodes/SceneTexture2.cpp \
	build/msvc6/src/Inventor/Win/nodes/Slider1.cpp \
	build/msvc6/src/Inventor/Win/nodes/Slider2.cpp \
	build/msvc6/src/Inventor/Win/nodes/SoGuiClickCounter.h \
	build/msvc6/src/Inventor/Win/nodes/SoGuiColorEditor.h \
	build/msvc6/src/Inventor/Win/nodes/SoGuiFrame.h \
	build/msvc6/src/Inventor/Win/nodes/SoGuiImage.h \
	build/msvc6/src/Inventor/Win/nodes/SoGuiLabel.h \
	build/msvc6/src/Inventor/Win/nodes/SoGuiMaterialEditor.h \
	build/msvc6/src/Inventor/Win/nodes/SoGuiNodes.h \
	build/msvc6/src/Inventor/Win/nodes/SoGuiPane.h \
	build/msvc6/src/Inventor/Win/nodes/SoGuiPosition.h \
	build/msvc6/src/Inventor/Win/nodes/SoGuiRadioButton.h \
	build/msvc6/src/Inventor/Win/nodes/SoGuiSceneTexture2.h \
	build/msvc6/src/Inventor/Win/nodes/SoGuiSlider1.h \
	build/msvc6/src/Inventor/Win/nodes/SoGuiSlider2.h \
	build/msvc6/src/Inventor/Win/nodes/SoGuiToggleButton.h \
	build/msvc6/src/Inventor/Win/nodes/SoGuiTranslation.h \
	build/msvc6/src/Inventor/Win/nodes/SoGuiViewpointWrapper.h \
	build/msvc6/src/Inventor/Win/nodes/SoGuiViewportFix.h \
	build/msvc6/src/Inventor/Win/nodes/ToggleButton.cpp \
	build/msvc6/src/Inventor/Win/nodes/Translation.cpp \
	build/msvc6/src/Inventor/Win/nodes/ViewpointWrapper.cpp \
	build/msvc6/src/Inventor/Win/nodes/ViewportFix.cpp \
	build/msvc6/src/Inventor/Win/viewers/SoGuiExaminerViewerP.h \
	build/msvc6/src/Inventor/Win/viewers/SoGuiFullViewerP.h \
	build/msvc6/src/Inventor/Win/viewers/SoGuiPlaneViewerP.h \
	build/msvc6/src/Inventor/Win/viewers/SoWinConstrainedViewer.cpp \
	build/msvc6/src/Inventor/Win/viewers/SoWinConstrainedViewer.h \
	build/msvc6/src/Inventor/Win/viewers/SoWinExaminerViewer.cpp \
	build/msvc6/src/Inventor/Win/viewers/SoWinExaminerViewer.h \
	build/msvc6/src/Inventor/Win/viewers/SoWinFlyViewer.cpp \
	build/msvc6/src/Inventor/Win/viewers/SoWinFlyViewer.h \
	build/msvc6/src/Inventor/Win/viewers/SoWinFullViewer.cpp \
	build/msvc6/src/Inventor/Win/viewers/SoWinFullViewer.h \
	build/msvc6/src/Inventor/Win/viewers/SoWinPlaneViewer.cpp \
	build/msvc6/src/Inventor/Win/viewers/SoWinPlaneViewer.h \
	build/msvc6/src/Inventor/Win/viewers/SoWinViewer.cpp \
	build/msvc6/src/Inventor/Win/viewers/SoWinViewer.h \
	build/msvc6/src/Inventor/Win/widgets/SoAnyThumbWheel.cpp \
	build/msvc6/src/Inventor/Win/widgets/SoAnyThumbWheel.h \
	build/msvc6/src/Inventor/Win/widgets/SoWinPopupMenu.cpp \
	build/msvc6/src/Inventor/Win/widgets/SoWinPopupMenu.h \
	build/msvc6/src/config-debug.h \
	build/msvc6/src/config-release.h \
	build/msvc6/src/config.h \
	build/msvc6/src/sowindefs.h \
	build/msvc6/install-headers.bat \
	build/msvc6/sowin1.dsp \
	build/msvc6/sowin1.dsw \
	build/msvc7/src/Inventor/Win/common/gl.h \
	build/msvc7/src/Inventor/Win/SoAny.cpp \
	build/msvc7/src/Inventor/Win/SoAny.h \
	build/msvc7/src/Inventor/Win/SoGuiComponentP.h \
	build/msvc7/src/Inventor/Win/SoGuiGLWidgetP.h \
	build/msvc7/src/Inventor/Win/SoGuiP.h \
	build/msvc7/src/Inventor/Win/SoWin.h \
	build/msvc7/src/Inventor/Win/SoWinBasic.h \
	build/msvc7/src/Inventor/Win/SoWinColorEditor.h \
	build/msvc7/src/Inventor/Win/SoWinCommon.cpp \
	build/msvc7/src/Inventor/Win/SoWinComponent.h \
	build/msvc7/src/Inventor/Win/SoWinComponentCommon.cpp \
	build/msvc7/src/Inventor/Win/SoWinCursor.cpp \
	build/msvc7/src/Inventor/Win/SoWinCursor.h \
	build/msvc7/src/Inventor/Win/SoWinGLWidget.h \
	build/msvc7/src/Inventor/Win/SoWinGLWidgetCommon.cpp \
	build/msvc7/src/Inventor/Win/SoWinMaterialEditor.h \
	build/msvc7/src/Inventor/Win/SoWinObject.cpp \
	build/msvc7/src/Inventor/Win/SoWinObject.h \
	build/msvc7/src/Inventor/Win/SoWinRenderArea.cpp \
	build/msvc7/src/Inventor/Win/SoWinRenderArea.h \
	build/msvc7/src/Inventor/Win/devices/SoGuiDeviceP.h \
	build/msvc7/src/Inventor/Win/devices/SoGuiInputFocusP.h \
	build/msvc7/src/Inventor/Win/devices/SoGuiKeyboardP.h \
	build/msvc7/src/Inventor/Win/devices/SoGuiMouseP.h \
	build/msvc7/src/Inventor/Win/devices/SoGuiSpaceballP.h \
	build/msvc7/src/Inventor/Win/devices/SoWinDevice.h \
	build/msvc7/src/Inventor/Win/devices/SoWinDeviceCommon.cpp \
	build/msvc7/src/Inventor/Win/devices/SoWinInputFocus.h \
	build/msvc7/src/Inventor/Win/devices/SoWinInputFocusCommon.cpp \
	build/msvc7/src/Inventor/Win/devices/SoWinKeyboard.h \
	build/msvc7/src/Inventor/Win/devices/SoWinKeyboardCommon.cpp \
	build/msvc7/src/Inventor/Win/devices/SoWinMouse.h \
	build/msvc7/src/Inventor/Win/devices/SoWinMouseCommon.cpp \
	build/msvc7/src/Inventor/Win/devices/SoWinSpaceball.h \
	build/msvc7/src/Inventor/Win/devices/SoWinSpaceballCommon.cpp \
	build/msvc7/src/Inventor/Win/devices/spwinput.h \
	build/msvc7/src/Inventor/Win/devices/spwinput_win32.c \
	build/msvc7/src/Inventor/Win/devices/spwinput_win32.h \
	build/msvc7/src/Inventor/Win/devices/spwinput_x11.cpp \
	build/msvc7/src/Inventor/Win/editors/SoWinColorEditor.cpp \
	build/msvc7/src/Inventor/Win/editors/SoWinColorEditor.h \
	build/msvc7/src/Inventor/Win/editors/SoWinMaterialEditor.cpp \
	build/msvc7/src/Inventor/Win/editors/SoWinMaterialEditor.h \
	build/msvc7/src/Inventor/Win/engines/Engines.cpp \
	build/msvc7/src/Inventor/Win/engines/Format.cpp \
	build/msvc7/src/Inventor/Win/engines/RadioGroup.cpp \
	build/msvc7/src/Inventor/Win/engines/SoGuiEngines.h \
	build/msvc7/src/Inventor/Win/engines/SoGuiFormat.h \
	build/msvc7/src/Inventor/Win/engines/SoGuiRadioGroup.h \
	build/msvc7/src/Inventor/Win/nodes/ClickCounter.cpp \
	build/msvc7/src/Inventor/Win/nodes/ColorEditor.cpp \
	build/msvc7/src/Inventor/Win/nodes/Frame.cpp \
	build/msvc7/src/Inventor/Win/nodes/Image.cpp \
	build/msvc7/src/Inventor/Win/nodes/Label.cpp \
	build/msvc7/src/Inventor/Win/nodes/MaterialEditor.cpp \
	build/msvc7/src/Inventor/Win/nodes/Nodes.cpp \
	build/msvc7/src/Inventor/Win/nodes/Pane.cpp \
	build/msvc7/src/Inventor/Win/nodes/Position.cpp \
	build/msvc7/src/Inventor/Win/nodes/RadioButton.cpp \
	build/msvc7/src/Inventor/Win/nodes/SceneTexture2.cpp \
	build/msvc7/src/Inventor/Win/nodes/Slider1.cpp \
	build/msvc7/src/Inventor/Win/nodes/Slider2.cpp \
	build/msvc7/src/Inventor/Win/nodes/SoGuiClickCounter.h \
	build/msvc7/src/Inventor/Win/nodes/SoGuiColorEditor.h \
	build/msvc7/src/Inventor/Win/nodes/SoGuiFrame.h \
	build/msvc7/src/Inventor/Win/nodes/SoGuiImage.h \
	build/msvc7/src/Inventor/Win/nodes/SoGuiLabel.h \
	build/msvc7/src/Inventor/Win/nodes/SoGuiMaterialEditor.h \
	build/msvc7/src/Inventor/Win/nodes/SoGuiNodes.h \
	build/msvc7/src/Inventor/Win/nodes/SoGuiPane.h \
	build/msvc7/src/Inventor/Win/nodes/SoGuiPosition.h \
	build/msvc7/src/Inventor/Win/nodes/SoGuiRadioButton.h \
	build/msvc7/src/Inventor/Win/nodes/SoGuiSceneTexture2.h \
	build/msvc7/src/Inventor/Win/nodes/SoGuiSlider1.h \
	build/msvc7/src/Inventor/Win/nodes/SoGuiSlider2.h \
	build/msvc7/src/Inventor/Win/nodes/SoGuiToggleButton.h \
	build/msvc7/src/Inventor/Win/nodes/SoGuiTranslation.h \
	build/msvc7/src/Inventor/Win/nodes/SoGuiViewpointWrapper.h \
	build/msvc7/src/Inventor/Win/nodes/SoGuiViewportFix.h \
	build/msvc7/src/Inventor/Win/nodes/ToggleButton.cpp \
	build/msvc7/src/Inventor/Win/nodes/Translation.cpp \
	build/msvc7/src/Inventor/Win/nodes/ViewpointWrapper.cpp \
	build/msvc7/src/Inventor/Win/nodes/ViewportFix.cpp \
	build/msvc7/src/Inventor/Win/viewers/SoGuiExaminerViewerP.h \
	build/msvc7/src/Inventor/Win/viewers/SoGuiFullViewerP.h \
	build/msvc7/src/Inventor/Win/viewers/SoGuiPlaneViewerP.h \
	build/msvc7/src/Inventor/Win/viewers/SoWinConstrainedViewer.cpp \
	build/msvc7/src/Inventor/Win/viewers/SoWinConstrainedViewer.h \
	build/msvc7/src/Inventor/Win/viewers/SoWinExaminerViewer.cpp \
	build/msvc7/src/Inventor/Win/viewers/SoWinExaminerViewer.h \
	build/msvc7/src/Inventor/Win/viewers/SoWinFlyViewer.cpp \
	build/msvc7/src/Inventor/Win/viewers/SoWinFlyViewer.h \
	build/msvc7/src/Inventor/Win/viewers/SoWinFullViewer.cpp \
	build/msvc7/src/Inventor/Win/viewers/SoWinFullViewer.h \
	build/msvc7/src/Inventor/Win/viewers/SoWinPlaneViewer.cpp \
	build/msvc7/src/Inventor/Win/viewers/SoWinPlaneViewer.h \
	build/msvc7/src/Inventor/Win/viewers/SoWinViewer.cpp \
	build/msvc7/src/Inventor/Win/viewers/SoWinViewer.h \
	build/msvc7/src/Inventor/Win/widgets/SoAnyThumbWheel.cpp \
	build/msvc7/src/Inventor/Win/widgets/SoAnyThumbWheel.h \
	build/msvc7/src/Inventor/Win/widgets/SoWinPopupMenu.cpp \
	build/msvc7/src/Inventor/Win/widgets/SoWinPopupMenu.h \
	build/msvc7/src/config.h \
	build/msvc7/src/config-debug.h \
	build/msvc7/src/config-release.h \
	build/msvc7/src/sowindefs.h \
	build/msvc7/install-headers.bat \
	build/msvc7/sowin1.sln \
	build/msvc7/sowin1.vcproj \
	build/msvc8/src/Inventor/Win/common/gl.h \
	build/msvc8/src/Inventor/Win/SoAny.cpp \
	build/msvc8/src/Inventor/Win/SoAny.h \
	build/msvc8/src/Inventor/Win/SoGuiComponentP.h \
	build/msvc8/src/Inventor/Win/SoGuiGLWidgetP.h \
	build/msvc8/src/Inventor/Win/SoGuiP.h \
	build/msvc8/src/Inventor/Win/SoWin.h \
	build/msvc8/src/Inventor/Win/SoWinBasic.h \
	build/msvc8/src/Inventor/Win/SoWinColorEditor.h \
	build/msvc8/src/Inventor/Win/SoWinCommon.cpp \
	build/msvc8/src/Inventor/Win/SoWinComponent.h \
	build/msvc8/src/Inventor/Win/SoWinComponentCommon.cpp \
	build/msvc8/src/Inventor/Win/SoWinCursor.cpp \
	build/msvc8/src/Inventor/Win/SoWinCursor.h \
	build/msvc8/src/Inventor/Win/SoWinGLWidget.h \
	build/msvc8/src/Inventor/Win/SoWinGLWidgetCommon.cpp \
	build/msvc8/src/Inventor/Win/SoWinMaterialEditor.h \
	build/msvc8/src/Inventor/Win/SoWinObject.cpp \
	build/msvc8/src/Inventor/Win/SoWinObject.h \
	build/msvc8/src/Inventor/Win/SoWinRenderArea.cpp \
	build/msvc8/src/Inventor/Win/SoWinRenderArea.h \
	build/msvc8/src/Inventor/Win/devices/SoGuiDeviceP.h \
	build/msvc8/src/Inventor/Win/devices/SoGuiInputFocusP.h \
	build/msvc8/src/Inventor/Win/devices/SoGuiKeyboardP.h \
	build/msvc8/src/Inventor/Win/devices/SoGuiMouseP.h \
	build/msvc8/src/Inventor/Win/devices/SoGuiSpaceballP.h \
	build/msvc8/src/Inventor/Win/devices/SoWinDevice.h \
	build/msvc8/src/Inventor/Win/devices/SoWinDeviceCommon.cpp \
	build/msvc8/src/Inventor/Win/devices/SoWinInputFocus.h \
	build/msvc8/src/Inventor/Win/devices/SoWinInputFocusCommon.cpp \
	build/msvc8/src/Inventor/Win/devices/SoWinKeyboard.h \
	build/msvc8/src/Inventor/Win/devices/SoWinKeyboardCommon.cpp \
	build/msvc8/src/Inventor/Win/devices/SoWinMouse.h \
	build/msvc8/src/Inventor/Win/devices/SoWinMouseCommon.cpp \
	build/msvc8/src/Inventor/Win/devices/SoWinSpaceball.h \
	build/msvc8/src/Inventor/Win/devices/SoWinSpaceballCommon.cpp \
	build/msvc8/src/Inventor/Win/devices/spwinput.h \
	build/msvc8/src/Inventor/Win/devices/spwinput_win32.c \
	build/msvc8/src/Inventor/Win/devices/spwinput_win32.h \
	build/msvc8/src/Inventor/Win/devices/spwinput_x11.cpp \
	build/msvc8/src/Inventor/Win/editors/SoWinColorEditor.cpp \
	build/msvc8/src/Inventor/Win/editors/SoWinColorEditor.h \
	build/msvc8/src/Inventor/Win/editors/SoWinMaterialEditor.cpp \
	build/msvc8/src/Inventor/Win/editors/SoWinMaterialEditor.h \
	build/msvc8/src/Inventor/Win/engines/Engines.cpp \
	build/msvc8/src/Inventor/Win/engines/Format.cpp \
	build/msvc8/src/Inventor/Win/engines/RadioGroup.cpp \
	build/msvc8/src/Inventor/Win/engines/SoGuiEngines.h \
	build/msvc8/src/Inventor/Win/engines/SoGuiFormat.h \
	build/msvc8/src/Inventor/Win/engines/SoGuiRadioGroup.h \
	build/msvc8/src/Inventor/Win/nodes/ClickCounter.cpp \
	build/msvc8/src/Inventor/Win/nodes/ColorEditor.cpp \
	build/msvc8/src/Inventor/Win/nodes/Frame.cpp \
	build/msvc8/src/Inventor/Win/nodes/Image.cpp \
	build/msvc8/src/Inventor/Win/nodes/Label.cpp \
	build/msvc8/src/Inventor/Win/nodes/MaterialEditor.cpp \
	build/msvc8/src/Inventor/Win/nodes/Nodes.cpp \
	build/msvc8/src/Inventor/Win/nodes/Pane.cpp \
	build/msvc8/src/Inventor/Win/nodes/Position.cpp \
	build/msvc8/src/Inventor/Win/nodes/RadioButton.cpp \
	build/msvc8/src/Inventor/Win/nodes/SceneTexture2.cpp \
	build/msvc8/src/Inventor/Win/nodes/Slider1.cpp \
	build/msvc8/src/Inventor/Win/nodes/Slider2.cpp \
	build/msvc8/src/Inventor/Win/nodes/SoGuiClickCounter.h \
	build/msvc8/src/Inventor/Win/nodes/SoGuiColorEditor.h \
	build/msvc8/src/Inventor/Win/nodes/SoGuiFrame.h \
	build/msvc8/src/Inventor/Win/nodes/SoGuiImage.h \
	build/msvc8/src/Inventor/Win/nodes/SoGuiLabel.h \
	build/msvc8/src/Inventor/Win/nodes/SoGuiMaterialEditor.h \
	build/msvc8/src/Inventor/Win/nodes/SoGuiNodes.h \
	build/msvc8/src/Inventor/Win/nodes/SoGuiPane.h \
	build/msvc8/src/Inventor/Win/nodes/SoGuiPosition.h \
	build/msvc8/src/Inventor/Win/nodes/SoGuiRadioButton.h \
	build/msvc8/src/Inventor/Win/nodes/SoGuiSceneTexture2.h \
	build/msvc8/src/Inventor/Win/nodes/SoGuiSlider1.h \
	build/msvc8/src/Inventor/Win/nodes/SoGuiSlider2.h \
	build/msvc8/src/Inventor/Win/nodes/SoGuiToggleButton.h \
	build/msvc8/src/Inventor/Win/nodes/SoGuiTranslation.h \
	build/msvc8/src/Inventor/Win/nodes/SoGuiViewpointWrapper.h \
	build/msvc8/src/Inventor/Win/nodes/SoGuiViewportFix.h \
	build/msvc8/src/Inventor/Win/nodes/ToggleButton.cpp \
	build/msvc8/src/Inventor/Win/nodes/Translation.cpp \
	build/msvc8/src/Inventor/Win/nodes/ViewpointWrapper.cpp \
	build/msvc8/src/Inventor/Win/nodes/ViewportFix.cpp \
	build/msvc8/src/Inventor/Win/viewers/SoGuiExaminerViewerP.h \
	build/msvc8/src/Inventor/Win/viewers/SoGuiFullViewerP.h \
	build/msvc8/src/Inventor/Win/viewers/SoGuiPlaneViewerP.h \
	build/msvc8/src/Inventor/Win/viewers/SoWinConstrainedViewer.cpp \
	build/msvc8/src/Inventor/Win/viewers/SoWinConstrainedViewer.h \
	build/msvc8/src/Inventor/Win/viewers/SoWinExaminerViewer.cpp \
	build/msvc8/src/Inventor/Win/viewers/SoWinExaminerViewer.h \
	build/msvc8/src/Inventor/Win/viewers/SoWinFlyViewer.cpp \
	build/msvc8/src/Inventor/Win/viewers/SoWinFlyViewer.h \
	build/msvc8/src/Inventor/Win/viewers/SoWinFullViewer.cpp \
	build/msvc8/src/Inventor/Win/viewers/SoWinFullViewer.h \
	build/msvc8/src/Inventor/Win/viewers/SoWinPlaneViewer.cpp \
	build/msvc8/src/Inventor/Win/viewers/SoWinPlaneViewer.h \
	build/msvc8/src/Inventor/Win/viewers/SoWinViewer.cpp \
	build/msvc8/src/Inventor/Win/viewers/SoWinViewer.h \
	build/msvc8/src/Inventor/Win/widgets/SoAnyThumbWheel.cpp \
	build/msvc8/src/Inventor/Win/widgets/SoAnyThumbWheel.h \
	build/msvc8/src/Inventor/Win/widgets/SoWinPopupMenu.cpp \
	build/msvc8/src/Inventor/Win/widgets/SoWinPopupMenu.h \
	build/msvc8/src/config.h \
	build/msvc8/src/config-debug.h \
	build/msvc8/src/config-release.h \
	build/msvc8/src/sowindefs.h \
	build/msvc8/install-headers.bat \
	build/msvc8/sowin1.sln \
	build/msvc8/sowin1.vcproj

# Target which is present to make it simple to only generate all the source
# files from the common sources.

built-sources: $(BUILT_SOURCES)

############################################################################

all-local: built-sources

install-exec-local: built-sources $(srcdir)/cfg/wrapmsvc.exe
	@$(NORMAL_INSTALL)
	@if @BUILD_WITH_MSVC@; then \
	  echo " $(mkinstalldirs) $(DESTDIR)$(bindir)"; \
	  $(mkinstalldirs) "$(DESTDIR)$(bindir)"; \
	  p=wrapmsvc.exe; \
	  echo " $(INSTALL_PROGRAM) $(top_srcdir)/cfg/$$p $(DESTDIR)$(bindir)/$$p"; \
	  $(INSTALL_PROGRAM) "$(top_srcdir)/cfg/$$p" "$(DESTDIR)$(bindir)/$$p"; \
	fi

install-data-local: built-sources

uninstall-local:
	@rm -f $(DESTDIR)$(bindir)/wrapmsvc.exe

# **************************************************************************
# misc rules for automatic Microsoft Windows packaging.
# main: `windows-packages'

windows-files:
	@if test -d windows; then :; else \
	  echo " mkdir windows"; \
	  mkdir windows; \
	fi
	@for file in $(top_srcdir)/packaging/windows/*.in; do \
	  basename=`echo $$file | sed 's%^.*/%%g; s%\.in$$%%'`; \
	  echo " config.status: generating windows/$$basename"; \
	  ./config.status --file=-:- >"windows/$$basename" <"$$file"; \
	done

windows-packages: windows-files
	@( cd windows; $(MAKE) VERSION=$(VERSION) )

# EOF ######################################################################

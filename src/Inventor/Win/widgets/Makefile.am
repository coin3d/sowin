############################################################################
##

include ../common/Makefile.common

## Process this file with automake to generate Makefile.in.

if BUILD_WITH_MSVC
noinst_LIBRARIES = widgets.lst
else
noinst_LTLIBRARIES = libSoWinWidgets.la
endif

## Remove any linklibraries detected by configure, as they are not
## needed in the submodules -- only in the toplevel libSoWin build.

INCLUDES = -I$(top_srcdir)/src
LIBS = 

## Handle built sourcecode files.

BUILT_SOURCES = \
	$(SoGuiAllBuiltFiles)

CLEANFILES = \
	$(SoGui_src_Inventor_Gui_widgets_BuiltMetaFiles)

DISTCLEANFILES = \
	$(SoGui_src_Inventor_Gui_widgets_BuiltFiles) \
	$(SoGui_src_Inventor_Gui_widgets_BuiltMetaFiles)

############################################################################
# libtool setup

libSoWinWidgets_la_SOURCES = \
	SoWinThumbWheel.cpp \
	SoWinThumbWheel.h \
	SoWinPopupMenu.cpp \
	SoWinPopupMenu.h \
	SoWinBitmapButton.cpp \
	SoWinBitmapButton.h \
        SoWinViewerPrefSheet.cpp \
        SoWinViewerPrefSheet.h

nodist_libSoWinWidgets_la_SOURCES = \
	$(SoGui_src_Inventor_Gui_widgets_BuiltFiles)
#	$(SoGui_src_Inventor_Gui_widgets_BuiltMetaFiles)

############################################################################
# custom setup

widgets_lst_SOURCES = \
	SoWinThumbWheel.cpp \
	SoWinThumbWheel.h \
	SoWinPopupMenu.cpp \
	SoWinPopupMenu.h \
	SoWinBitmapButton.cpp \
	SoWinBitmapButton.h \
        SoWinViewerPrefSheet.cpp \
        SoWinViewerPrefSheet.h

nodist_widgets_lst_SOURCES = \
	$(SoGui_src_Inventor_Gui_widgets_BuiltFiles)
#	$(SoGui_src_Inventor_Gui_widgets_BuiltMetaFiles)

widgets.lst: Makefile $(widgets_lst_OBJECTS)
	@echo "Linking widgets.lst..."; \
	rm -f $@; \
	for i in $(widgets_lst_OBJECTS); do echo $$i >>$@; done

# EOF ######################################################################

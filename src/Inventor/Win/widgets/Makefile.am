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

BUILT_SOURCES = \
	SoAnyPopupMenu.h \
	SoAnyPopupMenu.cpp \
	SoAnyThumbWheel.h \
	SoAnyThumbWheel.cpp

DISTCLEANFILES = \
	$(BUILT_SOURCES)

WidgetSources = \
	SoWinThumbWheel.cpp \
	SoWinThumbWheel.h \
	SoWinPopupMenu.cpp \
	SoWinPopupMenu.h \
	SoWinBitmapButton.cpp \
	SoWinBitmapButton.h \
        SoWinViewerPrefSheet.cpp \
        SoWinViewerPrefSheet.h

############################################################################

SoAnyPopupMenu.h: $(top_srcdir)/src/Inventor/Win/common/SoAnyPopupMenu.h.in
	@( cd $(top_builddir); \
	   $(MAKE) src/Inventor/Win/widgets/SoAnyPopupMenu.h )

SoAnyPopupMenu.cpp: $(top_srcdir)/src/Inventor/Win/common/SoAnyPopupMenu.cpp.in
	@( cd $(top_builddir); \
	   $(MAKE) src/Inventor/Win/widgets/SoAnyPopupMenu.cpp )

SoAnyThumbWheel.h: $(top_srcdir)/src/Inventor/Win/common/SoAnyThumbWheel.h.in
	@( cd $(top_builddir); \
	   $(MAKE) src/Inventor/Win/widgets/SoAnyThumbWheel.h )

SoAnyThumbWheel.cpp: $(top_srcdir)/src/Inventor/Win/common/SoAnyThumbWheel.cpp.in
	@( cd $(top_builddir); \
	   $(MAKE) src/Inventor/Win/widgets/SoAnyThumbWheel.cpp )

############################################################################
# libtool setup

libSoWinWidgets_la_SOURCES = \
	$(WidgetSources)

nodist_libSoWinWidgets_la_SOURCES = \
	$(BUILT_SOURCES)

############################################################################
# custom setup

widgets_lst_SOURCES = \
	$(WidgetSources)

nodist_widgets_lst_SOURCES = \
	$(BUILT_SOURCES)

widgets.lst: Makefile $(widgets_lst_OBJECTS)
	@echo "Linking widgets.lst..."; \
	rm -f $@; \
	for i in $(widgets_lst_OBJECTS); do echo $$i >>$@; done

# EOF ######################################################################

## Process this file with automake to generate Makefile.in.

if BUILD_WITH_MSVC
noinst_LIBRARIES = widgets.lst
else
noinst_LTLIBRARIES = libSoWinWidgets.la
endif

## Remove any linklibraries detected by configure, as they are not
## needed in the submodules -- only in the toplevel libSoWin build.

INCLUDES = -I$(top_builddir)/src -I$(top_srcdir)/src
LIBS = 

BUILT_SOURCES = \
	SoAnyPopupMenu.h \
	SoAnyPopupMenu.cpp \
	SoAnyThumbWheel.h \
	SoAnyThumbWheel.cpp

WIDGETSOURCES = \
	$(BUILT_SOURCES) \
	SoWinThumbWheel.cpp \
	SoWinThumbWheel.h \
	SoWinPopupMenu.cpp \
	SoWinPopupMenu.h \
	SoWinBitmapButton.cpp \
	SoWinBitmapButton.h

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
	$(WIDGETSOURCES)

############################################################################
# custom setup

widgets_lst_SOURCES = \
	$(WIDGETSOURCES)

widgets.lst: Makefile $(widgets_lst_OBJECTS)
	@echo "Linking widgets.lst..."; \
	echo $(CC) /LST:widgets.lst \
	  $(widgets_lst_OBJECTS); \
	$(CC) /LST:widgets.lst \
	  $(widgets_lst_OBJECTS);

# EOF ######################################################################

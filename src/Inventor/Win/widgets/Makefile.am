## Process this file with automake to generate Makefile.in.

noinst_LTLIBRARIES = libSoWinWidgets.la

## Remove any linklibraries detected by configure, as they are not
## needed in the submodules -- only in the toplevel libSoWin build.

INCLUDES = -I$(top_builddir)/src -I$(top_srcdir)/src
LIBS = 

BUILT_SOURCES = \
	SoAnyPopupMenu.h \
	SoAnyPopupMenu.cpp \
	SoAnyThumbWheel.h \
	SoAnyThumbWheel.cpp \


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

## All source files used when building this submodule, including all
## headers.

libSoWinWidgets_la_SOURCES = \
	$(BUILT_SOURCES) \
	SoWinThumbWheel.cpp \
	SoWinThumbWheel.h \
	SoWinPopupMenu.cpp \
	SoWinPopupMenu.h \
	SoWinBitmapButton.cpp \
	SoWinBitmapButton.h

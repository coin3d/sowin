############################################################################
## SoWin/Makefile.am
## $Id$

SUBDIRS = . src/Inventor/Win

bin_SCRIPTS = soxt-config

BUILT_SOURCES = \
	sowindefs.h \
	src/Inventor/Win/SoWinBasic.h \
	src/Inventor/Win/SoWinRenderArea.h \
	src/Inventor/Win/SoWinRenderArea.cpp

noinst_DATA = $(BUILT_SOURCES)

############################################################################

built-sources: $(BUILT_SOURCES)

sowindefs.h: $(top_srcdir)/sowindefs.h.in
	@CONFIG_HEADERS= CONFIG_FILES=$@:sowindefs.h.in ./config.status

src/Inventor/Xt/SoXtBasic.h: \
  $(top_srcdir)/src/Inventor/Xt/common/SoGuiBasic.h.in
	@CONFIG_FILES=-:src/Inventor/Xt/common/SoGuiBasic.h.in CONFIG_HEADERS= \
	./config.status | CONFIG_FILES= CONFIG_HEADERS=$@:- ./config.status

src/Inventor/Xt/SoXtRenderArea.h: \
  $(top_srcdir)/src/Inventor/Xt/common/SoGuiRenderArea.h.in
	@CONFIG_HEADERS= \
	CONFIG_FILES=$@:src/Inventor/Xt/common/SoGuiRenderArea.h.in \
	./config.status

src/Inventor/Xt/SoXtRenderArea.cpp: \
  $(top_srcdir)/src/Inventor/Xt/common/SoGuiRenderArea.cpp.in
	@CONFIG_HEADERS= \
	CONFIG_FILES=$@:src/Inventor/Xt/common/SoGuiRenderArea.cpp.in \
	./config.status

############################################################################

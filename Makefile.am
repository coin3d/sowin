############################################################################
## SoWin/Makefile.am
## $Id$

SUBDIRS = . src/Inventor/Win

bin_SCRIPTS = sowin-config

BUILT_SOURCES = \
	sowindefs.h \
	src/Inventor/Win/SoWinBasic.h \
	src/Inventor/Win/SoWinRenderArea.h \
	src/Inventor/Win/SoWinRenderArea.cpp \
	src/Inventor/Win/viewers/SoWinViewer.h \
	src/Inventor/Win/viewers/SoWinViewer.cpp

noinst_DATA = $(BUILT_SOURCES)

############################################################################

built-sources: $(BUILT_SOURCES)

sowindefs.h: $(top_srcdir)/sowindefs.h.in
	@CONFIG_HEADERS= CONFIG_FILES=$@:sowindefs.h.in ./config.status

src/Inventor/Win/SoWinBasic.h: \
  $(top_srcdir)/src/Inventor/Win/common/SoGuiBasic.h.in
	@CONFIG_FILES=-:src/Inventor/Win/common/SoGuiBasic.h.in CONFIG_HEADERS= \
	./config.status | CONFIG_FILES= CONFIG_HEADERS=$@:- ./config.status

src/Inventor/Win/SoWinRenderArea.h: \
  $(top_srcdir)/src/Inventor/Win/common/SoGuiRenderArea.h.in
	@CONFIG_HEADERS= \
	CONFIG_FILES=$@:src/Inventor/Win/common/SoGuiRenderArea.h.in \
	./config.status

src/Inventor/Win/SoWinRenderArea.cpp: \
  $(top_srcdir)/src/Inventor/Win/common/SoGuiRenderArea.cpp.in
	@CONFIG_HEADERS= \
	CONFIG_FILES=$@:src/Inventor/Win/common/SoGuiRenderArea.cpp.in \
	./config.status

src/Inventor/Win/viewers/SoWinViewer.h: \
  $(top_srcdir)/src/Inventor/Win/common/SoGuiViewer.h.in
	@CONFIG_HEADERS= \
	CONFIG_FILES=$@:src/Inventor/Win/common/SoGuiViewer.h.in \
	./config.status

src/Inventor/Win/viewers/SoWinViewer.cpp: \
  $(top_srcdir)/src/Inventor/Win/common/SoGuiViewer.cpp.in
	@CONFIG_HEADERS= \
	CONFIG_FILES=$@:src/Inventor/Win/common/SoGuiViewer.cpp.in \
	./config.status

#	src/Inventor/Win/common/viewers/SoAnyFullViewer.h \
#	src/Inventor/Win/common/viewers/SoAnyFullViewer.cpp \
#	src/Inventor/Win/common/viewers/SoAnyExaminerViewer.h \
#	src/Inventor/Win/common/viewers/SoAnyExaminerViewer.cpp \
#	src/Inventor/Win/common/viewers/SoAnyPlaneViewer.h \
#	src/Inventor/Win/common/viewers/SoAnyPlaneViewer.cpp \

############################################################################


















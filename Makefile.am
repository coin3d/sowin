## Process this file with automake to generate Makefile.in.

SUFFIXES = .cpp .h .m4 .in .o .lo .Plo .TPlo

SUBDIRS = . src/Inventor/Win

bin_SCRIPTS = sowin-config

BUILT_SOURCES = \
	sowin-config \
	sowindefs.h \
	src/Inventor/Win/SoWinBasic.h \
	src/Inventor/Win/SoWinCursors.h \
	src/Inventor/Win/SoWinCursors.cpp \
	src/Inventor/Win/SoWinRenderArea.h \
	src/Inventor/Win/SoWinRenderArea.cpp \
	src/Inventor/Win/viewers/SoWinViewer.h \
	src/Inventor/Win/viewers/SoWinViewer.cpp \
	src/Inventor/Win/viewers/SoAnyFullViewer.h \
	src/Inventor/Win/viewers/SoAnyFullViewer.cpp \
	src/Inventor/Win/viewers/SoAnyExaminerViewer.h \
	src/Inventor/Win/viewers/SoAnyExaminerViewer.cpp \
	src/Inventor/Win/viewers/SoAnyPlaneViewer.h \
	src/Inventor/Win/viewers/SoAnyPlaneViewer.cpp \
	src/Inventor/Win/widgets/SoAnyThumbWheel.h \
	src/Inventor/Win/widgets/SoAnyThumbWheel.cpp \
	src/Inventor/Win/widgets/SoAnyPopupMenu.h \
	src/Inventor/Win/widgets/SoAnyPopupMenu.cpp \
	src/Inventor/Win/devices/spwinput.h \
	src/Inventor/Win/devices/spwinput_x11.cpp

# This is necessary to set up a hook somewhere in the generated Makefile
# so the sources are actually built.
noinst_DATA = $(BUILT_SOURCES)

sowin-config: sowin-config.in

EXTRA_DIST = conf-macros/sowin.m4

m4datadir = $(datadir)/aclocal
m4data_DATA = conf-macros/sowin.m4

############################################################################

# Target which is present to make it simple to only generate the
# sourcefiles from the common sources.
built-sources: $(BUILT_SOURCES)

sowindefs.h: $(srcdir)/sowindefs.h.in
	@./config.status --file=sowindefs.h

src/Inventor/Win/SoWinBasic.h: $(srcdir)/src/Inventor/Win/common/SoGuiBasic.h.in
	@./config.status \
	  --file=-:$(srcdir)/src/Inventor/Win/common/SoGuiBasic.h.in | \
	  ./config.status --header=$@:-

src/Inventor/Win/SoWinCursors.h: \
  $(srcdir)/src/Inventor/Win/common/SoGuiCursors.h.in
	@./config.status --file=$@:src/Inventor/Win/common/SoGuiCursors.h.in

src/Inventor/Win/SoWinCursors.cpp: \
  $(srcdir)/src/Inventor/Win/common/SoGuiCursors.cpp.in
	@./config.status --file=$@:src/Inventor/Win/common/SoGuiCursors.cpp.in

src/Inventor/Win/SoWinRenderArea.h: \
  $(srcdir)/src/Inventor/Win/common/SoGuiRenderArea.h.in
	@./config.status --file=$@:src/Inventor/Win/common/SoGuiRenderArea.h.in

src/Inventor/Win/SoWinRenderArea.cpp: \
  $(srcdir)/src/Inventor/Win/common/SoGuiRenderArea.cpp.in
	@./config.status --file=$@:src/Inventor/Win/common/SoGuiRenderArea.cpp.in

src/Inventor/Win/viewers/SoWinViewer.h: \
  $(srcdir)/src/Inventor/Win/common/SoGuiViewer.h.in
	@./config.status --file=$@:src/Inventor/Win/common/SoGuiViewer.h.in

src/Inventor/Win/viewers/SoWinViewer.cpp: \
  $(srcdir)/src/Inventor/Win/common/SoGuiViewer.cpp.in
	@./config.status --file=$@:src/Inventor/Win/common/SoGuiViewer.cpp.in

src/Inventor/Win/viewers/SoAnyFullViewer.h: \
  $(srcdir)/src/Inventor/Win/common/SoAnyFullViewer.h.in
	@./config.status --file=$@:src/Inventor/Win/common/SoAnyFullViewer.h.in

src/Inventor/Win/viewers/SoAnyFullViewer.cpp: \
  $(srcdir)/src/Inventor/Win/common/SoAnyFullViewer.cpp.in
	@./config.status --file=$@:src/Inventor/Win/common/SoAnyFullViewer.cpp.in

src/Inventor/Win/viewers/SoAnyExaminerViewer.h: \
  $(srcdir)/src/Inventor/Win/common/SoAnyExaminerViewer.h.in
	@./config.status \
	  --file=$@:src/Inventor/Win/common/SoAnyExaminerViewer.h.in

src/Inventor/Win/viewers/SoAnyExaminerViewer.cpp: \
  $(srcdir)/src/Inventor/Win/common/SoAnyExaminerViewer.cpp.in
	@./config.status \
	  --file=$@:src/Inventor/Win/common/SoAnyExaminerViewer.cpp.in

src/Inventor/Win/viewers/SoAnyPlaneViewer.h: \
  $(srcdir)/src/Inventor/Win/common/SoAnyPlaneViewer.h.in
	@./config.status \
	  --file=$@:src/Inventor/Win/common/SoAnyPlaneViewer.h.in

src/Inventor/Win/viewers/SoAnyPlaneViewer.cpp: \
  $(srcdir)/src/Inventor/Win/common/SoAnyPlaneViewer.cpp.in
	@./config.status \
	  --file=$@:src/Inventor/Win/common/SoAnyPlaneViewer.cpp.in

src/Inventor/Win/widgets/SoAnyThumbWheel.h: \
  $(srcdir)/src/Inventor/Win/common/SoAnyThumbWheel.h.in
	@./config.status --file=$@:src/Inventor/Win/common/SoAnyThumbWheel.h.in

src/Inventor/Win/widgets/SoAnyThumbWheel.cpp: \
  $(srcdir)/src/Inventor/Win/common/SoAnyThumbWheel.cpp.in
	@./config.status --file=$@:src/Inventor/Win/common/SoAnyThumbWheel.cpp.in

src/Inventor/Win/widgets/SoAnyPopupMenu.h: \
  $(srcdir)/src/Inventor/Win/common/SoAnyPopupMenu.h.in
	@./config.status --file=$@:src/Inventor/Win/common/SoAnyPopupMenu.h.in

src/Inventor/Win/widgets/SoAnyPopupMenu.cpp: \
  $(srcdir)/src/Inventor/Win/common/SoAnyPopupMenu.cpp.in
	@./config.status --file=$@:src/Inventor/Win/common/SoAnyPopupMenu.cpp.in

src/Inventor/Win/devices/spwinput.h: \
  $(srcdir)/src/Inventor/Win/common/spwinput.h.in
	@./config.status --file=$@:src/Inventor/Win/common/spwinput.h.in

src/Inventor/Win/devices/spwinput_x11.cpp: \
  $(srcdir)/src/Inventor/Win/common/spwinput_x11.cpp.in
	@./config.status --file=$@:src/Inventor/Win/common/spwinput_x11.cpp.in

############################################################################

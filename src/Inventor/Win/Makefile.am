############################################################################

SUBDIRS = devices widgets viewers

############################################################################

INCLUDES = -I$(top_builddir)/src -I$(top_srcdir)/src

lib_LTLIBRARIES = libSoWin@SUFFIX@.la

BUILT_SOURCES = \
	SoAny.h \
	SoAny.cpp \
	SoWinBasic.h \
	SoWinObject.cpp \
	SoWinObject.h \
	SoWinRenderArea.h \
	SoWinRenderArea.cpp

noinst_DATA = $(BUILT_SOURCES)

############################################################################

libSoWin@SUFFIX@_la_SOURCES = \
	$(BUILT_SOURCES) \
	SoWin.h \
	SoWin.cpp \
	SoWinComponent.h \
	SoWinComponent.cpp \
	SoWinGLWidget.h \
	SoWinGLWidget.cpp

libSoWin@SUFFIX@_la_LIBADD = \
	devices/libSoWinDevices.la \
	viewers/libSoWinViewers.la \
	widgets/libSoWinWidgets.la

libSoWin@SUFFIX@_la_LDFLAGS = \
        -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)

############################################################################

libSoWinincdir = $(includedir)/Inventor/Win

libSoWininc_HEADERS = \
	$(top_builddir)/src/Inventor/Win/SoWinBasic.h \
	$(top_srcdir)/src/Inventor/Win/SoWin.h \
	$(top_builddir)/src/Inventor/Win/SoWinObject.h \
	$(top_srcdir)/src/Inventor/Win/SoWinComponent.h \
	$(top_srcdir)/src/Inventor/Win/SoWinGLWidget.h \
	$(top_builddir)/src/Inventor/Win/SoWinRenderArea.h

############################################################################

SoWinBasic.h: $(srcdir)/common/SoGuiBasic.h.in
	@( cd $(top_builddir); $(MAKE) built-sources )

SoAny.h: $(srcdir)/common/SoAny.h.in
	@( cd $(top_builddir); $(MAKE) built-sources )

SoAny.cpp: $(srcdir)/common/SoAny.cpp.in
	@( cd $(top_builddir); $(MAKE) built-sources )

SoWinObject.h: $(srcdir)/common/SoGuiObject.h.in
	@( cd $(top_builddir); $(MAKE) built-sources )

SoWinObject.cpp: $(srcdir)/common/SoGuiObject.cpp.in
	@( cd $(top_builddir); $(MAKE) built-sources )

SoWinRenderArea.h: $(srcdir)/common/SoGuiRenderArea.h.in
	@( cd $(top_builddir); $(MAKE) built-sources )

SoWinRenderArea.cpp: $(srcdir)/common/SoGuiRenderArea.cpp.in
	@( cd $(top_builddir); $(MAKE) built-sources )

############################################################################

sowin@SOWIN_MAJOR_VERSION@@SUFFIX@.lib: Makefile \
  $(libSoWin@SUFFIX@_la_OBJECTS) $(libSoWin@SUFFIX@_la_DEPENDENCIES)
	@basename="sowin@SOWIN_MAJOR_VERSION@@SUFFIX@"; \
	rm -f "$$basename.lib" "$$basename.dll"; \
	if @BUILD_WITH_MSVC@; then \
	  echo "Linking $@..."; \
	  echo $(CC) $(LDFLAGS) $(LIBFLAGS) \
	        `echo $(libSoWin@SUFFIX@_la_OBJECTS) | sed 's%\.lo%.obj%g'` \
	        $(libSoWin@SUFFIX@_la_LIBADD) $(LIBS); \
	  $(CC) $(LDFLAGS) $(LIBFLAGS) \
	        `echo $(libSoWin@SUFFIX@_la_OBJECTS) | sed 's%\.lo%.obj%g'` \
	        $(libSoWin@SUFFIX@_la_LIBADD) $(LIBS); \
	else \
	  touch "$$basename.lib" "$$basename.dll"; \
	fi

all-local: sowin@SOWIN_MAJOR_VERSION@@SUFFIX@.lib

# **************************************************************************

install-exec-hook: sowin@SOWIN_MAJOR_VERSION@@SUFFIX@.lib
	@basename="sowin@SOWIN_MAJOR_VERSION@@SUFFIX@"; \
	for ext in dll pdb; do \
	  file="$$basename.$$ext"; \
	  if test -s "$$file"; then \
	    $(mkinstalldirs) "$(DESTDIR)$(bindir)"; \
	    echo " $(INSTALL_PROGRAM)" "$$file" "$(DESTDIR)$(bindir)/$$file"; \
	    $(INSTALL_PROGRAM) "$$file" "$(DESTDIR)$(bindir)/$$file"; \
	  fi \
	done;

install-data-hook: sowin@SOWIN_MAJOR_VERSION@@SUFFIX@.lib
	@basename="sowin@SOWIN_MAJOR_VERSION@@SUFFIX@"; \
	for ext in lib; do \
	  file="$$basename.$$ext"; \
	  if test -s "$$file"; then \
	    $(mkinstalldirs) "$(DESTDIR)$(libdir)"; \
	    echo " $(INSTALL_DATA)" "$$file" "$(DESTDIR)$(libdir)/$$file"; \
	    $(INSTALL_DATA) "$$file" "$(DESTDIR)$(libdir)/$$file"; \
	  fi \
	done;

uninstall: uninstall-am
	@basename="sowin@SOWIN_MAJOR_VERSION@@SUFFIX@"; \
	for file in \
	  "$(DESTDIR)$(libdir)/$$basename.lib" \
	  "$(DESTDIR)$(bindir)/$$basename.dll" \
	  "$(DESTDIR)$(bindir)/$$basename.pdb"; do \
	  if test -f "$$file"; then \
	    echo " rm -f" "$$file"; \
	    rm -f "$$file"; \
	  fi \
	done; \
	baseincdir="$(DESTDIR)$(includedir)/Inventor/Win"; \
	for dir in \
	  "$$baseincdir/devices" \
	  "$$baseincdir/viewers"; do
	  if test -d "$$dir"; then \
	    echo " rmdir" "$$dir"; \
	    rmdir "$$dir"; \
	  fi \
	done;

# EOF **********************************************************************

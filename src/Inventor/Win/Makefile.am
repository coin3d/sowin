############################################################################

SUBDIRS = devices widgets viewers

############################################################################

INCLUDES = -I$(top_srcdir)/src

if BUILD_WITH_MSVC
lib_LIBRARIES = sowin@SOWIN_MAJOR_VERSION@@SUFFIX@.lib
else
lib_LTLIBRARIES = libSoWin@SUFFIX@.la
endif

BUILT_SOURCES = \
	SoAny.h \
	SoAny.cpp \
	SoWinBasic.h \
	SoWinObject.cpp \
	SoWinObject.h \
	SoWinCursors.cpp \
	SoWinCursors.h \
	SoWinRenderArea.h \
	SoWinRenderArea.cpp

SoWinSources = \
	SoWin.h \
	SoWin.cpp \
	SoWinComponent.h \
	SoWinComponent.cpp \
	SoWinGLWidget.h \
	SoWinGLWidget.cpp \
	Win32API.cpp \
	Win32API.h

noinst_DATA = $(BUILT_SOURCES)

############################################################################
# libtool setup

libSoWin@SUFFIX@_la_SOURCES = \
	$(SoWinSources)

nodist_libSoWin@SUFFIX@_la_SOURCES = \
	$(BUILT_SOURCES)

libSoWin@SUFFIX@_la_LIBADD = \
	devices/libSoWinDevices.la \
	viewers/libSoWinViewers.la \
	widgets/libSoWinWidgets.la

libSoWin@SUFFIX@_la_LDFLAGS = \
        -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)

############################################################################
# alternative custom setup

sowin@SOWIN_MAJOR_VERSION@@SUFFIX@_lib_SOURCES = \
	$(SoWinSources)

nodist_sowin@SOWIN_MAJOR_VERSION@@SUFFIX@_lib_SOURCES = \
	$(BUILT_SOURCES)

sowin@SOWIN_MAJOR_VERSION@@SUFFIX@_lib_LIBADD = \
	devices/devices.lst \
	viewers/viewers.lst \
	widgets/widgets.lst

############################################################################

SoWinincdir = $(includedir)/Inventor/Win

SoWininc_HEADERS = \
	$(top_srcdir)/src/Inventor/Win/SoWin.h \
	$(top_srcdir)/src/Inventor/Win/SoWinComponent.h \
	$(top_srcdir)/src/Inventor/Win/SoWinGLWidget.h

nodist_SoWininc_HEADERS = \
	$(top_builddir)/src/Inventor/Win/SoWinBasic.h \
	$(top_builddir)/src/Inventor/Win/SoWinObject.h \
	$(top_builddir)/src/Inventor/Win/SoWinCursors.h \
	$(top_builddir)/src/Inventor/Win/SoWinRenderArea.h

install-SoWinincHEADERS: $(SoWininc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(SoWinincdir)
	@list='$(SoWininc_HEADERS)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  src="$$d$$p"; dst="$(DESTDIR)$(SoWinincdir)/$$f"; \
	  if cmp -s "$$src" "$$dst"; then :; else \
	    echo " $(INSTALL_HEADER) $$src $$dst"; \
	    $(INSTALL_HEADER) "$$src" "$$dst"; \
	  fi \
	done

install-nodist_SoWinincHEADERS: $(nodist_SoWininc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(SoWinincdir)
	@list='$(nodist_SoWininc_HEADERS)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  src="$$d$$p"; dst="$(DESTDIR)$(SoWinincdir)/$$f"; \
	  if cmp -s "$$src" "$$dst"; then :; else \
	    echo " $(INSTALL_HEADER) $$src $$dst"; \
	    $(INSTALL_HEADER) "$$src" "$$dst"; \
	  fi \
	done

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

SoWinCursors.h: $(srcdir)/common/SoGuiCursors.h.in
	@( cd $(top_builddir); $(MAKE) built-sources )

SoWinCursors.cpp: $(srcdir)/common/SoGuiCursors.cpp.in
	@( cd $(top_builddir); $(MAKE) built-sources )

SoWinRenderArea.h: $(srcdir)/common/SoGuiRenderArea.h.in
	@( cd $(top_builddir); $(MAKE) built-sources )

SoWinRenderArea.cpp: $(srcdir)/common/SoGuiRenderArea.cpp.in
	@( cd $(top_builddir); $(MAKE) built-sources )

############################################################################

sowin@SOWIN_MAJOR_VERSION@@SUFFIX@.lib: Makefile \
  $(sowin@SOWIN_MAJOR_VERSION@@SUFFIX@_lib_OBJECTS) \
  $(sowin@SOWIN_MAJOR_VERSION@@SUFFIX@_lib_DEPENDENCIES)
	@basename="sowin@SOWIN_MAJOR_VERSION@@SUFFIX@"; \
	rm -f "$$basename.lib" "$$basename.dll"; \
	echo "Linking $@..."; \
	echo $(CC) $(LDFLAGS) $(LIBFLAGS) \
	      $(sowin@SOWIN_MAJOR_VERSION@@SUFFIX@_lib_OBJECTS) \
	      $(sowin@SOWIN_MAJOR_VERSION@@SUFFIX@_lib_LIBADD) $(LIBS); \
	$(CC) $(LDFLAGS) $(LIBFLAGS) \
	      $(sowin@SOWIN_MAJOR_VERSION@@SUFFIX@_lib_OBJECTS) \
	      $(sowin@SOWIN_MAJOR_VERSION@@SUFFIX@_lib_LIBADD) $(LIBS)

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

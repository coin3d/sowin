############################################################################

SUBDIRS = devices widgets viewers

############################################################################

INCLUDES = -I$(top_builddir)/src -I$(top_srcdir)/src

lib_LTLIBRARIES = libSoWin.la

BUILT_SOURCES = \
	SoWinBasic.h \
	SoWinObject.cpp \
	SoWinObject.h \
	SoWinRenderArea.h \
	SoWinRenderArea.cpp

noinst_DATA = $(BUILT_SOURCES)

############################################################################

libSoWin_la_SOURCES = \
	$(BUILT_SOURCES) \
	SoWin.h \
	SoWin.cpp \
	SoWinComponent.h \
	SoWinComponent.cpp \
	SoWinGLWidget.h \
	SoWinGLWidget.cpp

libSoWin_la_LIBADD = \
	devices/libSoWinDevices.la \
	viewers/libSoWinViewers.la \
	widgets/libSoWinWidgets.la

libSoWin_la_LDFLAGS = \
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

SoWinObject.h: $(srcdir)/common/SoGuiObject.h.in
	@( cd $(top_builddir); $(MAKE) built-sources )

SoWinObject.cpp: $(srcdir)/common/SoGuiObject.cpp.in
	@( cd $(top_builddir); $(MAKE) built-sources )

SoWinRenderArea.h: $(srcdir)/common/SoGuiRenderArea.h.in
	@( cd $(top_builddir); $(MAKE) built-sources )

SoWinRenderArea.cpp: $(srcdir)/common/SoGuiRenderArea.cpp.in
	@( cd $(top_builddir); $(MAKE) built-sources )

############################################################################


#### Additional "native" Make rules #########################################


## Rule for linking up a .DLL on MSWindows with MSVC++.
##
## Short explanation of what the shell-code does: tests if the C
## compiler is our MSVC++ wrapper script, and if so: properly link the
## DLL. If not, just make an empty sowin{version}.dll file so the
## install-exec-hook knows when to _not_ install the .dll.

sowin@SOWIN_MAJOR_VERSION@.dll: $(libSoWin_la_OBJECTS) $(libSoWin_la_DEPENDENCIES)
	@rm -f sowin@SOWIN_MAJOR_VERSION@.dll && \
	if @BUILD_WITH_MSVC@; then \
	  echo "Linking DLL..."; \
	  $(CC) @DLLFLAGS@ /out:sowin@SOWIN_MAJOR_VERSION@.dll $(LDFLAGS) \
	        `echo $(libSoWin_la_OBJECTS) | sed 's%\.lo%.obj%g'` \
	        $(libSoWin_la_LIBADD) $(LIBS); \
	else \
	  touch sowin@SOWIN_MAJOR_VERSION@.dll; \
	fi

## This hook will be run at the end of a ``make install''.
##
## The single action taken is to install the sowin.dll and sowin.lib
## files (if they have been built properly).

install-exec-hook: sowin@SOWIN_MAJOR_VERSION@.dll
	@if test -s sowin@SOWIN_MAJOR_VERSION@.dll; then \
	  echo "Installing sowin@SOWIN_MAJOR_VERSION@.dll"; \
	  for e in dll lib pdb; do \
	    file="sowin@SOWIN_MAJOR_VERSION@.$$e"; \
	    if test -f $$file; then \
	      $(INSTALL_DATA) $$file $(DESTDIR)$(libdir)/$$file; \
	    fi \
	  done \
	fi

uninstall: uninstall-am
	@for e in dll lib pdb; do \
	  file="$(DESTDIR)$(libdir)/sowin@SOWIN_MAJOR_VERSION@.$$e"; \
	  if test -f "$$file"; then \
	    echo rm -f "$$file"; \
	    rm -f "$$file"; \
	  fi \
	done


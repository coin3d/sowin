############################################################################
## SoWin/src/Inventor/Win/Makefile.am
## $Id$

lib_LTLIBRARIES = libSoWin.la

SUBDIRS = devices widgets viewers

INCLUDES = -I$(top_builddir)/src -I$(top_srcdir)/src -I$(top_builddir)/data

BUILT_SOURCES = \
	SoWinBasic.h \
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
        devices/libSoWinDevices.la

############################################################################

SoWin.cpp: SoWinBasic.h
SoWinComponent.cpp: SoWinBasic.h
SoWinGLWidget.cpp: SoWinBasic.h

SoWinBasic.h: $(srcdir)/common/SoGuiBasic.h.in
	@( cd $(top_builddir); $(MAKE) built-sources )

SoWinRenderArea.h: $(srcdir)/common/SoGuiRenderArea.h.in
	@( cd $(top_builddir); $(MAKE) built-sources )

SoWinRenderArea.cpp: $(srcdir)/common/SoGuiRenderArea.cpp.in
	@( cd $(top_builddir); $(MAKE) built-sources )

############################################################################

libSoWinincdir = $(includedir)/Inventor/Win

libSoWininc_HEADERS = \
	SoWin.h \
	SoWinComponent.h \
	SoWinGLWidget.h \
	$(top_builddir)/src/Inventor/Win/SoWinBasic.h \
	$(top_builddir)/src/Inventor/Win/SoWinRenderArea.h

install-libSoWinincHEADERS: $(libSoWininc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(libSoWinincdir)
	@list='$(libSoWininc_HEADERS)'; for p in $$list; do \
	  if test -f "$$p"; then d= ; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " $(INSTALL_DATA) $$d$$p $(DESTDIR)$(libSoWinincdir)/$$f"; \
	  $(INSTALL_DATA) $$d$$p $(DESTDIR)$(libSoWinincdir)/$$f; \
	done

uninstall-libSoWinincHEADERS:
	@$(NORMAL_UNINSTALL)
	@list='$(libSoWininc_HEADERS)'; for p in $$list; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " rm -f $(DESTDIR)$(libSoWinincdir)/$$f"; \
	  rm -f $(DESTDIR)$(libSoWinincdir)/$$f; \
	done


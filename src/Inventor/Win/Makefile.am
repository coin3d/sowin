############################################################################
## So@Gui@/src/Inventor/@Gui@/makefile.am

include common/Makefile.common

############################################################################
##

SUBDIRS = devices viewers widgets

INCLUDES = -I$(top_srcdir)/src -I$(top_builddir)/data

BUILT_SOURCES = \
	$(SoGuiAllBuiltFiles)

CLEANFILES = \
	$(SoGui_src_Inventor_Gui_BuiltMetaFiles)

DISTCLEANFILES = \
	$(SoGui_src_Inventor_Gui_BuiltFiles) \
	$(SoGui_src_Inventor_Gui_BuiltMetaFiles)

############################################################################

if BUILD_WITH_MSVC
lib_LIBRARIES = sowin@SOWIN_MAJOR_VERSION@@SUFFIX@.lib
else
lib_LTLIBRARIES = libSoWin@SUFFIX@.la
endif

############################################################################
# libtool setup

libSoWin@SUFFIX@_la_SOURCES = \
	SoWin.cpp \
	SoWinComponent.cpp \
	SoWinComponentP.h \
	SoWinGLWidget.cpp \
	SoWinGLWidgetP.h \
	Win32API.cpp \
	Win32API.h

nodist_libSoWin@SUFFIX@_la_SOURCES = \
	$(SoGui_src_Inventor_Gui_BuiltFiles)
#	$(SoGui_src_Inventor_Gui_BuiltMetaFiles)

libSoWin@SUFFIX@_la_LIBADD = \
	devices/libSoWinDevices.la \
	viewers/libSoWinViewers.la \
	widgets/libSoWinWidgets.la

libSoWin@SUFFIX@_la_LDFLAGS = \
        -version-info $(LT_CURRENT):$(LT_REVISION):$(LT_AGE)

############################################################################
# custom setup

sowin@SOWIN_MAJOR_VERSION@@SUFFIX@_lib_SOURCES = \
	SoWin.cpp \
	SoWinComponent.cpp \
	SoWinComponentP.h \
	SoWinGLWidget.cpp \
	SoWinGLWidgetP.h \
	Win32API.cpp \
	Win32API.h

nodist_sowin@SOWIN_MAJOR_VERSION@@SUFFIX@_lib_SOURCES = \
	$(SoGui_src_Inventor_Gui_BuiltFiles)
#	$(SoGui_src_Inventor_Gui_BuiltMetaFiles)

sowin@SOWIN_MAJOR_VERSION@@SUFFIX@_lib_LIBADD = \
	devices/devices.lst \
	viewers/viewers.lst \
	widgets/widgets.lst

############################################################################
# header installation

SoWinincdir = $(includedir)/Inventor/Win
SoWininc_HEADERS =

nodist_SoWininc_HEADERS = \
	SoWin.h \
	SoWinBasic.h \
	SoWinObject.h \
	SoWinCursor.h \
	SoWinComponent.h \
	SoWinGLWidget.h \
	SoWinRenderArea.h

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
	    $(sowin@SOWIN_MAJOR_VERSION@@SUFFIX@_lib_LIBADD) $(LIBS);

############################################################################

install-exec-local:
	@basename="sowin@SOWIN_MAJOR_VERSION@@SUFFIX@"; \
	for ext in dll pdb; do \
	  file="$$basename.$$ext"; \
	  if test -f "$$file"; then \
	    $(mkinstalldirs) "$(DESTDIR)$(bindir)"; \
	    echo " $(INSTALL_PROGRAM)" "$$file" "$(DESTDIR)$(bindir)/$$file"; \
	    $(INSTALL_PROGRAM) "$$file" "$(DESTDIR)$(bindir)/$$file"; \
	  fi \
	done

install-data-local:
	@basename="sowin@SOWIN_MAJOR_VERSION@@SUFFIX@"; \
	for ext in lib; do \
	  file="$$basename.$$ext"; \
	  if test -f "$$file"; then \
	    $(mkinstalldirs) "$(DESTDIR)$(libdir)"; \
	    echo " $(INSTALL_DATA)" "$$file" "$(DESTDIR)$(libdir)/$$file"; \
	    $(INSTALL_DATA) "$$file" "$(DESTDIR)$(libdir)/$$file"; \
	  fi \
	done

uninstall-local: uninstall-SoWinincHEADERS uninstall-nodist_SoWinincHEADERS
	@basename="sowin@SOWIN_MAJOR_VERSION@@SUFFIX@"; \
	for ext in dll pdb lib; do \
	  file="$(DESTDIR)$(bindir)/$$basename.$$ext"; \
	  if test -f "$$file"; then \
	    echo " rm -f" "$$file"; \
	    echo rm -f "$$file"; \
	  fi \
	done; \
	baseincdir="$(DESTDIR)$(includedir)/Inventor/Win"; \
	for dir in \
	  "$$baseincdir/devices" \
	  "$$baseincdir/viewers" \
	  "$$baseincdir"; do \
	  if test -d "$$dir"; then \
	    echo " rmdir" "$$dir"; \
	    rmdir "$$dir" &>/dev/null; \
	  fi \
	done; \
	:

# EOF **********************************************************************

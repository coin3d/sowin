############################################################################
## Makefile.am

include src/Inventor/Win/common/Makefile.common

############################################################################
##

SUFFIXES = .cpp .h .m4 .in .o .lo .Plo .TPlo

############################################################################
## 

if BUILD_HTMLPAGES
HTMLDIR = html
else
HTMLDIR =
endif

if BUILD_LIBRARY
# Material editor(s) not part of the public API yet, so there's
# no point yet in installing the material data.
#LIBDIR = data src
LIBDIR = src
else
LIBDIR =
endif

SUBDIRS = . $(LIBDIR) man $(HTMLDIR)

BUILT_SOURCES = \
	$(SoGuiAllBuiltFiles)

CLEANFILES = \
	sowin@SOWIN_MAJOR_VERSION@.dsp \
	sowin@SOWIN_MAJOR_VERSION@.dsw \
	$(SoGui_BuiltMetaFiles)

DISTCLEANFILES = \
	libtool \
	$(SoGui_BuiltFiles) \
	$(SoGui_BuiltMetaFiles)

if BUILD_LIBRARY

bin_SCRIPTS = so@gui@-config

m4datadir = $(datadir)/aclocal
# Don't replace "win" with "@gui@" here, it will pukk up
# for ``make dist''.
dist_m4data_DATA = cfg/sowin.m4

cfgdatadir = $(datadir)/Coin/conf
cfgdata_DATA = so@gui@-@CONFIG@.cfg

endif

EXTRA_DIST = \
	LICENSE.GPL \
	bootstrap \
	packaging/windows/Makefile.in \
	packaging/windows/bfheader.nsi.in \
	packaging/windows/footer.nsi.in \
	packaging/windows/heading.nsi.in \
	packaging/windows/middle.nsi.in \
	packaging/windows/post.nsi.in \
	packaging/windows/sowin-sdk.html.in \
	$(SoGuiCommonDistFiles)

# Target which is present to make it simple to only generate all the source
# files from the common sources.

built-sources: $(BUILT_SOURCES)

############################################################################

all-local: built-sources

install-exec-local: built-sources $(srcdir)/cfg/wrapmsvc.exe
	@$(NORMAL_INSTALL)
	@if @BUILD_WITH_MSVC@; then \
	  echo " $(mkinstalldirs) $(DESTDIR)$(bindir)"; \
	  $(mkinstalldirs) "$(DESTDIR)$(bindir)"; \
	  p=wrapmsvc.exe; \
	  echo " $(INSTALL_PROGRAM) $(top_srcdir)/cfg/$$p $(DESTDIR)$(bindir)/$$p"; \
	  $(INSTALL_PROGRAM) "$(top_srcdir)/cfg/$$p" "$(DESTDIR)$(bindir)/$$p"; \
	fi

install-data-local: built-sources

# **************************************************************************
# misc rules for automatic Microsoft Windows packaging.
# main: `windows-packages'

windows-files:
	@if test -d windows; then :; else \
	  echo " mkdir windows"; \
	  mkdir windows; \
	fi
	@for file in $(top_srcdir)/packaging/windows/*.in; do \
	  basename=`echo $$file | sed 's%^.*/%%g; s%\.in$$%%'`; \
	  echo " config.status: generating windows/$$basename"; \
	  ./config.status --file=-:- >"windows/$$basename" <"$$file"; \
	done

windows-packages: windows-files
	@( cd windows; $(MAKE) VERSION=$(VERSION) )

# EOF ######################################################################

############################################################################
## SoWin/src/Inventor/Win/engines/Makefile.am

include ../common/Makefile.common

if BUILD_WITH_MSVC
noinst_LIBRARIES = engines.lst
else
noinst_LTLIBRARIES = libSoWinEngines.la
endif

DEFAULT_INCLUDES = -I$(top_builddir)/src -I$(top_srcdir)/src
LIBS =

BUILT_SOURCES = \
	$(SoGuiAllBuiltFiles)

CLEANFILES = \
	$(SoGui_src_Inventor_Gui_engines_BuiltMetaFiles)

DISTCLEANFILES = \
	$(SoGui_src_Inventor_Gui_engines_BuiltFiles) \
	$(SoGui_src_Inventor_Gui_engines_BuiltMetaFiles)

############################################################################

libSoWinEngines_la_SOURCES =

nodist_libSoWinEngines_la_SOURCES = \
	$(SoGui_src_Inventor_Gui_engines_BuiltFiles) \
	$(SoGui_src_Inventor_Gui_engines_BuiltMetaFiles)

############################################################################

engines_lst_SOURCES = 

nodist_engines_lst_SOURCES = \
	$(SoGui_src_Inventor_Gui_engines_BuiltFiles)
#	$(SoGui_src_Inventor_Gui_engines_BuiltMetaFiles)

engines.lst: Makefile $(engines_lst_OBJECTS)
	@echo "Linking engines.lst..."; \
	rm -f $@; \
	for i in $(engines_lst_OBJECTS); do echo $$i >>$@; done

############################################################################
# Headers are kept private.

SoWinEnginesincdir = $(includedir)/Inventor/@Gui@/engines

SoWinEnginesinc_HEADERS =

############################################################################

############################################################################
##

include ../common/Makefile.common

INCLUDES = -I$(top_srcdir)/src

LIBS =

BUILT_SOURCES = \
	$(SoGuiAllBuiltFiles)

CLEANFILES = \
	$(SoGui_src_Inventor_Gui_devices_BuiltFiles)

DISTCLEANFILES = \
	$(SoGui_src_Inventor_Gui_devices_BuiltFiles) \
	$(SoGui_src_Inventor_Gui_devices_BuiltMetaFiles) \
	SoWinInputFocus.h \
	SoWinKeyboard.h \
	SoWinMouse.h \
	SoWinSpaceball.h

## Process this file with automake to generate Makefile.in.

if BUILD_WITH_MSVC
noinst_LIBRARIES = devices.lst
else
noinst_LTLIBRARIES = libSoWinDevices.la
endif

############################################################################
# libtool setup

libSoWinDevices_la_SOURCES = \
	SoWinDevice.cpp \
	SoWinDevice.h \
	SoWinInputFocus.cpp \
	SoWinKeyboard.cpp \
	SoWinMouse.cpp \
	SoWinSpaceball.cpp

nodist_libSoWinDevices_la_SOURCES = \
	$(SoGui_src_Inventor_Gui_devices_BuiltFiles)
#	$(SoGui_src_Inventor_Gui_devices_BuiltMetaFiles)

############################################################################
# custom setup

devices_lst_SOURCES = \
	SoWinDevice.h \
	SoWinDevice.cpp \
	SoWinInputFocus.cpp \
	SoWinKeyboard.cpp \
	SoWinMouse.cpp \
	SoWinSpaceball.cpp

nodist_devices_lst_SOURCES = \
	$(SoGui_src_Inventor_Gui_devices_BuiltFiles)
#	$(SoGui_src_Inventor_Gui_devices_BuiltMetaFiles)

devices.lst: Makefile $(devices_lst_OBJECTS)
	@echo "Linking devices.lst..."; \
	rm -f $@; \
	for i in $(devices_lst_OBJECTS); do echo $$i >>$@; done

############################################################################
## Header file installation information.

SoWinDevicesincdir = $(includedir)/Inventor/Win/devices
SoWinDevicesinc_HEADERS = \
	SoWinDevice.h

nodist_SoWinDevicesinc_HEADERS = \
	SoWinInputFocus.h \
	SoWinKeyboard.h \
	SoWinMouse.h \
	SoWinSpaceball.h

install-SoWinDevicesincHEADERS: $(SoWinDevicesinc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(SoWinDevicesincdir)
	@list='$(SoWinDevicesinc_HEADERS)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  src="$$d$$p"; dst="$(DESTDIR)$(SoWinDevicesincdir)/$$f"; \
	  if cmp -s "$$src" "$$dst"; then :; else \
	    echo " $(INSTALL_HEADER) $$src $$dst"; \
	    $(INSTALL_HEADER) "$$src" "$$dst"; \
	  fi \
	done

install-nodist_SoWinDevicesincHEADERS: $(nodist_SoWinDevicesinc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(SoWinDevicesincdir)
	@list='$(nodist_SoWinDevicesinc_HEADERS)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  src="$$d$$p"; dst="$(DESTDIR)$(SoWinDevicesincdir)/$$f"; \
	  if cmp -s "$$src" "$$dst"; then :; else \
	    echo " $(INSTALL_HEADER) $$src $$dst"; \
	    $(INSTALL_HEADER) "$$src" "$$dst"; \
	  fi \
	done

# EOF ######################################################################

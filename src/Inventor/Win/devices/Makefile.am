############################################################################
## SoWin/src/Inventor/Win/devices/Makefile.am
## $Id$

if BUILD_WITH_MSVC
noinst_LIBRARIES = devices.lst
else
noinst_LTLIBRARIES = libSoWinDevices.la
endif

INCLUDES = -I$(top_srcdir)/src

BUILT_SOURCES =

DEVICESOURCES = \
	$(BUILT_SOURCES) \
	SoWinDevice.h \
	SoWinDevice.cpp \
	SoWinInputFocus.h \
	SoWinInputFocus.cpp \
	SoWinKeyboard.h \
	SoWinKeyboard.cpp \
	SoWinMouse.h \
	SoWinMouse.cpp \
	SoWinSpaceball.h \
	SoWinSpaceball.cpp

libSoWinDevices_la_SOURCES = \
	$(DEVICESOURCES)

devices_lst_SOURCES = \
	$(DEVICESOURCES)

############################################################################

devices.lst: Makefile $(devices_lst_OBJECTS)
	@echo "Linking devices.lst..."; \
	rm -f $@; \
	for i in $(devices_lst_OBJECTS); do echo $$i >>$@; done

############################################################################

SoWinDevicesincdir = $(includedir)/Inventor/Win/devices
SoWinDevicesinc_HEADERS = \
	SoWinDevice.h \
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

# EOF ######################################################################

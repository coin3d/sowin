############################################################################
## SoWin/src/Inventor/Win/devices/Makefile.am
## $Id$

if BUILD_WITH_MSVC
noinst_LIBRARIES = devices.lst
else
noinst_LTLIBRARIES = libSoWinDevices.la
endif

INCLUDES = -I$(top_builddir)/src -I$(top_srcdir)/src

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

libSoWinDevicesincdir = $(includedir)/Inventor/Win/devices

libSoWinDevicesinc_HEADERS = \
	SoWinDevice.h \
	SoWinInputFocus.h \
	SoWinKeyboard.h \
	SoWinMouse.h \
	SoWinSpaceball.h

# EOF ######################################################################

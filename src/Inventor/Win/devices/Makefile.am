############################################################################
## SoWin/src/Inventor/Win/devices/Makefile.am
## $Id$

noinst_LTLIBRARIES = libSoWinDevices.la

INCLUDES = -I$(top_builddir)/src -I$(top_srcdir)/src

BUILT_SOURCES =

libSoWinDevices_la_SOURCES = \
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

############################################################################

SoWinInputFocus.cpp: ../SoWinBasic.h
SoWinKeyboard.cpp: ../SoWinBasic.h
SoWinMouse.cpp: ../SoWinBasic.h
SoWinSpaceball.cpp: ../SoWinBasic.h

../SoWinBasic.h: $(top_srcdir)/src/Inventor/Win/common/SoGuiBasic.h.in
	( cd $(top_builddir); $(MAKE) built-sources )

############################################################################

libSoWinDevicesincdir = $(includedir)/Inventor/Win/devices

libSoWinDevicesinc_HEADERS = \
	SoWinDevice.h \
	SoWinInputFocus.h \
	SoWinKeyboard.h \
	SoWinMouse.h \
	SoWinSpaceball.h

install-libSoWinDevicesincHEADERS: $(libSoWinDevicesinc_HEADERS)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(libSoWinDevicesincdir)
	@list='$(libSoWinDevicesinc_HEADERS)'; for p in $$list; do \
	  if test -f "$$p"; then d= ; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " $(INSTALL_DATA) $$d$$p $(DESTDIR)$(libSoWinDevicesincdir)/$$f"; \
	  $(INSTALL_DATA) $$d$$p $(DESTDIR)$(libSoWinDevicesincdir)/$$f; \
	done

uninstall-libSoWinDevicesincHEADERS:
	@$(NORMAL_UNINSTALL)
	@list='$(libSoWinDevicesinc_HEADERS)'; for p in $$list; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " rm -f $(DESTDIR)$(libSoWinDevicesincdir)/$$f"; \
	  rm -f $(DESTDIR)$(libSoWinDevicesincdir)/$$f; \
	done


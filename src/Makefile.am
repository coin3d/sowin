
SUBDIRS = . Inventor

EXTRA_DIST = \
	sowindefs.h.in

DISTCLEANFILES = \
	sowindefs.h

sowindefs.h: $(srcdir)/sowindefs.h.in
	@( cd $(top_builddir); $(MAKE) src/sowindefs.h )

install-data-local: sowindefs.h
	@( cd $(top_builddir); $(MAKE) built-sources )

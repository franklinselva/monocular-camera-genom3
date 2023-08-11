
lib_LTLIBRARIES = libMonocularCamera_codels.la

libMonocularCamera_codels_la_SOURCES  =	MonocularCamera_c_types.h
libMonocularCamera_codels_la_SOURCES +=	MonocularCamera_codels.c
libMonocularCamera_codels_la_SOURCES +=	MonocularCamera_publish_codels.c

libMonocularCamera_codels_la_CPPFLAGS =	$(requires_CFLAGS)
libMonocularCamera_codels_la_LIBADD   =	$(requires_LIBS)
libMonocularCamera_codels_la_CPPFLAGS+=	$(codels_requires_CFLAGS)
libMonocularCamera_codels_la_LIBADD  +=	$(codels_requires_LIBS)
libMonocularCamera_codels_la_LDFLAGS  =	-release $(PACKAGE_VERSION)


# idl  mappings
BUILT_SOURCES=	MonocularCamera_c_types.h
CLEANFILES=	${BUILT_SOURCES}

MonocularCamera_c_types.h: ${top_srcdir}/camera.gen
	${GENOM3}  mappings \
	  -MD -MF .deps/$@.d -MT $@ --signature -l c $< >$@

-include .deps/MonocularCamera_c_types.h.d

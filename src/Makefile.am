lib_LTLIBRARIES = libkv.la

libkv_la_SOURCES = \
		libkv/tchdb.c \
		libkv/tcrdb.c \
		libkv/libmemcached.c

nobase_include_HEADERS = \
		libkv/tchdb.h \
		libkv/tcrdb.h \
		libkv/libmemcached.h \
		libkv.h

# -version-info CURRENT:REVISION:AGE
libkv_la_LDFLAGS = -version-info 1:0:0


check_PROGRAMS = \
		test_tchdb \
		test_libmemcached

TESTS = $(check_PROGRAMS)

test_tchdb_SOURCES = test_tchdb.c
test_tchdb_LDADD  = -ltokyocabinet -L. libkv.la

test_libmemcached_SOURCES = test_libmemcached.c
test_libmemcached_LDADD  = -lmemcached -L. libkv.la


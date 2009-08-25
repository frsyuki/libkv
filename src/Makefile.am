lib_LTLIBRARIES = libkv.la
lib_LTLIBRARIES += libkvpp.la

libkv_la_SOURCES = \
		libkv/tchdb.c \
		libkv/tcrdb.c \
		libkv/libmemcached.c

libkvpp_la_SOURCES = \
		libkv.cpp

nobase_include_HEADERS = \
		libkv/tchdb.h \
		libkv/tcrdb.h \
		libkv/libmemcached.h \
		libkv.h

nobase_include_HEADERS += \
		libkv/tchdb.hpp \
		libkv/tcrdb.hpp \
		libkv/libmemcached.hpp \
		libkv.hpp

# -version-info CURRENT:REVISION:AGE
libkv_la_LDFLAGS   = -version-info 1:0:0
libkvpp_la_LDFLAGS = -version-info 1:0:0


check_PROGRAMS = \
		test_tchdb \
		test_tchdbpp \
		test_tcrdb \
		test_tcrdbpp \
		test_libmemcached \
		test_libmemcachedpp

TESTS = $(check_PROGRAMS)

test_tchdb_SOURCES = test_tchdb.c
test_tchdb_LDADD  = -ltokyocabinet -L. -lkv

test_tcrdb_SOURCES = test_tcrdb.c
test_tcrdb_LDADD  = -ltokyotyrant -L. -lkv

test_libmemcached_SOURCES = test_libmemcached.c
test_libmemcached_LDADD  = -lmemcached -L. -lkv


test_tchdbpp_SOURCES = test_tchdbpp.cpp
test_tchdbpp_LDADD  = -ltokyocabinet -L. -lkvpp -lkv

test_tcrdbpp_SOURCES = test_tcrdbpp.cpp
test_tcrdbpp_LDADD  = -ltokyotyrant -L. -lkvpp -lkv

test_libmemcachedpp_SOURCES = test_libmemcachedpp.cpp
test_libmemcachedpp_LDADD  = -lmemcached -L. -lkvpp -lkv


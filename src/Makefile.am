lib_LTLIBRARIES = libkv.la libkvpp.la

libkv_la_SOURCES =
check_PROGRAMS =


if USE_TC
libkv_la_SOURCES += libkv/tcadb.c
#check_PROGRAMS += test_tcadb test_tcadbpp
#test_tcadb_SOURCES = test_tcadb.c
#test_tcadb_LDADD  = -ltokyocabinet -L. -lkv
#test_tcadbpp_SOURCES = test_tcadbpp.cpp
#test_tcadbpp_LDADD  = -ltokyocabinet -L. -lkvpp

libkv_la_SOURCES += libkv/tcbdb.c
#check_PROGRAMS += test_tcbdb test_tcbdbpp
#test_tcbdb_SOURCES = test_tcbdb.c
#test_tcbdb_LDADD  = -ltokyocabinet -L. -lkv
#test_tcbdbpp_SOURCES = test_tcbdbpp.cpp
#test_tcbdbpp_LDADD  = -ltokyocabinet -L. -lkvpp

libkv_la_SOURCES += libkv/tchdb.c
check_PROGRAMS += test_tchdb test_tchdbpp
test_tchdb_SOURCES = test_tchdb.c
test_tchdb_LDADD  = -ltokyocabinet -L. -lkv
test_tchdbpp_SOURCES = test_tchdbpp.cpp
test_tchdbpp_LDADD  = -ltokyocabinet -L. -lkvpp
endif


if USE_TT
libkv_la_SOURCES += libkv/tcrdb.c
check_PROGRAMS += test_tcrdb test_tcrdbpp
test_tcrdb_SOURCES = test_tcrdb.c
test_tcrdb_LDADD  = -ltokyotyrant -L. -lkv
test_tcrdbpp_SOURCES = test_tcrdbpp.cpp
test_tcrdbpp_LDADD  = -ltokyotyrant -L. -lkvpp
endif


if USE_LIBMEMCACHED
libkv_la_SOURCES += libkv/libmemcached.c
check_PROGRAMS += test_libmemcached test_libmemcachedpp
test_libmemcached_SOURCES = test_libmemcached.c
test_libmemcached_LDADD  = -lmemcached -L. -lkv
test_libmemcachedpp_SOURCES = test_libmemcachedpp.cpp
test_libmemcachedpp_LDADD  = -lmemcached -L. -lkvpp
endif


check_PROGRAMS += test_msgpack
test_msgpack_SOURCES = test_msgpack.c
test_msgpack_LDADD  = -ltokyocabinet -lmsgpack -L. -lkvpp


libkvpp_la_SOURCES = libkv.cpp
libkvpp_la_LIBADD = libkv.la


nobase_include_HEADERS = \
		libkv/tcadb.h \
		libkv/tcbdb.h \
		libkv/tchdb.h \
		libkv/tcrdb.h \
		libkv/libmemcached.h \
		libkv.h \
		libkv/tcadb.hpp \
		libkv/tcbdb.hpp \
		libkv/tchdb.hpp \
		libkv/tcrdb.hpp \
		libkv/libmemcached.hpp \
		libkv.hpp

# -version-info CURRENT:REVISION:AGE
libkv_la_LDFLAGS   = -version-info 1:0:0
libkvpp_la_LDFLAGS = -version-info 1:0:0


TESTS = $(check_PROGRAMS)


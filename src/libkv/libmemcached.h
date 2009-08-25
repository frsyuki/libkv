#ifndef LIBKV_LIBMEMCACHED_H__
#define LIBKV_LIBMEMCACHED_H__

#include <libmemcached/memcached.h>
#include "libkv.h"

#ifdef __cplusplus
extern "C" {
#endif


bool libkv_libmemcached_init(libkv_t*);

bool libkv_libmemcached_add(libkv_t*,
		const char* hostname, unsigned int port);

bool libkv_libmemcached_add_udp(libkv_t*,
		const char* hostname, unsigned int port);

bool libkv_libmemcached_add_unix_socket(libkv_t*,
		const char* path);

bool libkv_libmemcached_add_list(libkv_t*,
		const char* server_strings);


#ifdef __cplusplus
}
#endif

#endif /* libkv/libmemcached.h */


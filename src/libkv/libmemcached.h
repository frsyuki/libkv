#include <libmemcached/memcached.h>
#include "libkv.h"

bool libkv_libmemcached_init(libkv*);

bool libkv_libmemcached_add(libkv*,
		const char* hostname, unsigned int port);

bool libkv_libmemcached_add_udp(libkv*,
		const char* hostname, unsigned int port);

bool libkv_libmemcached_add_unix_socket(libkv*,
		const char* path);

bool libkv_libkemcached_add_list(libkv*,
		const char* server_strings);


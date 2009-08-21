#include "libkv/libmemcached.h"
#include <libmemcached/memcached.h>

static void* kv_get(memcached_st* c,
		const void* key, size_t keylen,
		size_t* result_vallen)
{
	uint32_t flags;
	memcached_return error;
	return memcached_get(c, key, keylen, result_vallen, &flags, &error);
}

static bool kv_put(memcached_st* c,
		const void* key, size_t keylen,
		const void* val, size_t vallen)
{
	return memcached_set(c, key, keylen, val, vallen, 0, 0)
		== MEMCACHED_SUCCESS;
}

static bool kv_del(memcached_st* c,
		const void* key, size_t keylen)
{
	return memcached_delete(c, key, keylen, 0)
		== MEMCACHED_SUCCESS;
}

static libkv_mget* kv_mget_new(memcached_st* c)
{
	// FIXME
	return NULL;
}

static bool kv_close(memcached_st* c)
{
	memcached_free(c);
	return true;
}


bool libkv_libmemcached_init(libkv* x)
{
	memcached_st* c = memcached_create(NULL);
	if(!c) {
		return false;
	}
	x->kv_get      = (void*)&kv_get;
	x->kv_put      = (void*)&kv_put;
	x->kv_del      = (void*)&kv_del;
	x->kv_mget_new = (void*)&kv_mget_new;
	x->kv_close    = (void*)&kv_close;
	x->data        = (void*)c;
	return true;
}

bool libkv_libmemcached_add(libkv* x,
		const char* hostname, unsigned int port)
{
	return memcached_server_add(x->data, hostname, port)
		== MEMCACHED_SUCCESS;
}

bool libkv_libmemcached_add_udp(libkv* x,
		const char* hostname, unsigned int port)
{
	return memcached_server_add_udp(x->data, hostname, port)
		== MEMCACHED_SUCCESS;
}

bool libkv_libmemcached_add_unix_socket(libkv* x,
		const char* path)
{
	return memcached_server_add_unix_socket(x->data, path)
		== MEMCACHED_SUCCESS;
}

bool libkv_libkemcached_add_list(libkv* x,
		const char* server_strings)
{
	memcached_return ret;
	memcached_server_st* list = memcached_servers_parse(server_strings);
	if(list == NULL) {
		return false;
	}
	ret = memcached_server_push(x->data, list);
	memcached_server_list_free(list);
	return ret == MEMCACHED_SUCCESS;
}


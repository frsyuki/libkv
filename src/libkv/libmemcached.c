/*
 * libkv
 *
 * Copyright (c) 2009 FURUHASHI Sadayuki
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include "libkv/libmemcached.h"
#include <libmemcached/memcached.h>

typedef struct kv_data {
	memcached_st* st;
	memcached_return err;
} kv_data;

static void* kv_get(kv_data* c,
		const void* key, size_t keylen,
		size_t* result_vallen)
{
	uint32_t flags;
	return memcached_get(c->st, key, keylen, result_vallen, &flags, &c->err);
}

static bool kv_put(kv_data* c,
		const void* key, size_t keylen,
		const void* val, size_t vallen)
{
	return (c->err = memcached_set(c->st, key, keylen, val, vallen, 0, 0))
		== MEMCACHED_SUCCESS;
}

static bool kv_del(kv_data* c,
		const void* key, size_t keylen)
{
	return (c->err = memcached_delete(c->st, key, keylen, 0))
		== MEMCACHED_SUCCESS;
}

static bool kv_close(kv_data* c)
{
	memcached_free(c->st);
	free(c);
	return true;
}

static const char* kv_errmsg(kv_data* c)
{
	return memcached_strerror(c->st, c->err);
}


typedef struct kv_mget_data {
	kv_data* c;
	char* lastbuf;
} kv_mget_data;

static const void* kv_mget_next(kv_mget_data* m,
		void* keybuf, size_t* keybuflen,
		size_t* result_vallen)
{
	uint32_t flags;
	if(m->lastbuf != NULL) {
		free(m->lastbuf);
		m->lastbuf = NULL;
	}
	m->lastbuf = memcached_fetch(m->c->st, keybuf, keybuflen,
			result_vallen, &flags, &m->c->err);
	if(m->c->err != MEMCACHED_SUCCESS) {
		return NULL;
	}
	return m->lastbuf;
}

static void kv_mget_free(kv_mget_data* m)
{
	if(m->lastbuf != NULL) {
		free(m->lastbuf);
	}
	free(m);
}

static bool kv_mget(kv_data* c, libkv_mget_data* mx,
		char** keys, size_t* keylens, size_t num)
{
	kv_mget_data* m = malloc(sizeof(kv_mget_data));
	if(m == NULL) {
		return NULL;
	}
	if(memcached_mget(c->st, keys, keylens, num)
			!= MEMCACHED_SUCCESS) {
		free(m);
		return false;
	}
	m->c = c;
	m->lastbuf = NULL;
	mx->kv_mget_next  = (void*)&kv_mget_next;
	mx->kv_mget_free  = (void*)&kv_mget_free;
	mx->data = (void*)m;
	return true;
}


memcached_st* libkv_get_libmemcached(libkv_t* x)
{
	kv_data* c = x->data;
	return c->st;
}

bool libkv_libmemcached_init(libkv_t* x)
{
	kv_data* kv = malloc(sizeof(kv_data));
	if(!kv) {
		return false;
	}

	memcached_st* st = memcached_create(NULL);
	if(!st) {
		free(kv);
		return false;
	}
	kv->st = st;
	kv->err = MEMCACHED_SUCCESS;

	x->kv_get    = (void*)&kv_get;
	x->kv_put    = (void*)&kv_put;
	x->kv_del    = (void*)&kv_del;
	x->kv_mget   = (void*)&kv_mget;
	x->kv_close  = (void*)&kv_close;
	x->kv_errmsg = (void*)&kv_errmsg;
	x->data = (void*)kv;
	return true;
}

bool libkv_libmemcached_add(libkv_t* x,
		const char* hostname, unsigned int port)
{
	kv_data* c = x->data;
	return (c->err = memcached_server_add(c->st, hostname, port))
		== MEMCACHED_SUCCESS;
}

bool libkv_libmemcached_add_udp(libkv_t* x,
		const char* hostname, unsigned int port)
{
	kv_data* c = x->data;
	return (c->err = memcached_server_add_udp(c->st, hostname, port))
		== MEMCACHED_SUCCESS;
}

bool libkv_libmemcached_add_unix_socket(libkv_t* x,
		const char* path)
{
	kv_data* c = x->data;
	return (c->err = memcached_server_add_unix_socket(c->st, path))
		== MEMCACHED_SUCCESS;
}

bool libkv_libmemcached_add_list(libkv_t* x,
		const char* server_strings)
{
	kv_data* c = x->data;
	memcached_server_st* list = memcached_servers_parse(server_strings);
	if(list == NULL) {
		return false;
	}
	c->err = memcached_server_push(c->st, list);
	memcached_server_list_free(list);
	return c->err == MEMCACHED_SUCCESS;
}

bool libkv_libmemcached_set_binary_protocol(libkv_t* x)
{
	return memcached_behavior_set(x->data, MEMCACHED_BEHAVIOR_BINARY_PROTOCOL, 1)
		== MEMCACHED_SUCCESS;
}


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
#include "libkv/tchdb.h"
#include <string.h>
#include <tcutil.h>

static void* kv_get(TCHDB* c,
		const void* key, size_t keylen,
		size_t* result_vallen)
{
	int vallen = 0;
	void* val = tchdbget(c, key, keylen, &vallen);
	*result_vallen = vallen;
	return val;
}

static bool kv_put(TCHDB* c,
		const void* key, size_t keylen,
		const void* val, size_t vallen)
{
	return tchdbput(c, key, keylen, val, vallen);
}

static bool kv_del(TCHDB* c,
		const void* key, size_t keylen)
{
	return tchdbout(c, key, keylen);
}

static bool kv_close(TCHDB* c)
{
	bool r = tchdbclose(c);
	tchdbdel(c);
	return r;
}

static const char* kv_errmsg(TCHDB* c)
{
	return tchdberrmsg(tchdbecode(c));
}


static const void* kv_mget_next(TCMAP* m,
		void* keybuf, size_t* keybuflen,
		size_t* result_vallen)
{
	int keylen;
	int vallen;
	const void* val;
	const void* key = tcmapiternext(m, &keylen);
	if(*keybuflen < keylen) {
		return NULL;
	}
	memcpy(keybuf, key, keylen);
	*keybuflen = keylen;
	val = tcmapget(m, key, keylen, &vallen);
	*result_vallen = vallen;
	return val;
}

static void kv_mget_free(TCMAP* m)
{
	tcmapdel(m);
}

static bool kv_mget(TCHDB* c, libkv_mget_data* mx,
		char** keys, size_t* keylens, size_t num)
{
	size_t i;
	TCMAP* m = tcmapnew();
	if(m == NULL) {
		return false;
	}
	for(i=0; i < num; ++i) {
		int vallen = 0;
		void* val = tchdbget(c, keys[i], keylens[i], &vallen);
		if(val) {
			tcmapput(m, keys[i], keylens[i], val, vallen);  // tcmapput doesn't fail!
			free(val);
		}
	}
	tcmapiterinit(m);  // tcmapiterinit doesn't fail!
	mx->kv_mget_next  = (void*)&kv_mget_next;
	mx->kv_mget_free  = (void*)&kv_mget_free;
	mx->data = (void*)m;
	return true;
}


TCHDB* libkv_get_tchdb(libkv_t* x)
{
	TCHDB* c = x->data;
	return c;
}

bool libkv_tchdb_init(libkv_t* x)
{
	TCHDB* c = tchdbnew();
	if(!c) {
		return false;
	}
	if(!tchdbsetmutex(c)) {
		tchdbdel(c);
		return false;
	}
	x->kv_get    = (void*)&kv_get;
	x->kv_put    = (void*)&kv_put;
	x->kv_del    = (void*)&kv_del;
	x->kv_mget   = (void*)&kv_mget;
	x->kv_close  = (void*)&kv_close;
	x->kv_errmsg = (void*)&kv_errmsg;
	x->data = (void*)c;
	return true;
}

bool libkv_tchdb_open(libkv_t* x,
		const char* path, int mode)
{
	TCHDB* c = x->data;
	return tchdbopen(c, path, mode);
}


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
#include "libkv/tcbdb.h"
#include <string.h>
#include <tcutil.h>

static void* kv_get(TCBDB* c,
		const void* key, size_t keylen,
		size_t* result_vallen)
{
	int vallen = 0;
	void* val = tcbdbget(c, key, keylen, &vallen);
	*result_vallen = vallen;
	return val;
}

static bool kv_put(TCBDB* c,
		const void* key, size_t keylen,
		const void* val, size_t vallen)
{
	return tcbdbput(c, key, keylen, val, vallen);
}

static bool kv_del(TCBDB* c,
		const void* key, size_t keylen)
{
	return tcbdbout(c, key, keylen);
}

static bool kv_close(TCBDB* c)
{
	bool r = tcbdbclose(c);
	tcbdbdel(c);
	return r;
}

static const char* kv_errmsg(TCBDB* c)
{
	return tcbdberrmsg(tcbdbecode(c));
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

static bool kv_mget(TCBDB* c, libkv_mget_data* mx,
		char** keys, size_t* keylens, size_t num)
{
	size_t i;
	TCMAP* m = tcmapnew();
	if(m == NULL) {
		return false;
	}
	for(i=0; i < num; ++i) {
		int vallen = 0;
		void* val = tcbdbget(c, keys[i], keylens[i], &vallen);
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


bool libkv_tcbdb_init(libkv_t* x)
{
	TCBDB* c = tcbdbnew();
	if(!c) {
		return false;
	}
	if(!tcbdbsetmutex(c)) {
		tcbdbdel(c);
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

bool libkv_tcbdb_open(libkv_t* x,
		const char* path, int mode)
{
	TCBDB* c = x->data;
	return tcbdbopen(c, path, mode);
}


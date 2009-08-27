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
#ifndef LIBKV_H__
#define LIBKV_H__

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct libkv_mget_data {
	const void* (*kv_mget_next)(void*,
			void* keybuf, size_t* keybuflen,
			size_t* result_vallen);

	void (*kv_mget_free)(void*);

	void* data;
} libkv_mget_data;


typedef struct libkv_t {
	void* (*kv_get)(void*,
		const void* key, size_t keylen,
		size_t* result_vallen);

	bool (*kv_put)(void*,
			const void* key, size_t keylen,
			const void* val, size_t vallen);

	bool (*kv_del)(void*,
			const void* key, size_t keylen);

	bool (*kv_mget)(void*, libkv_mget_data*,
			char** keys, size_t* keylens, size_t num);

	bool (*kv_close)(void*);

	const char* (*kv_errmsg)(void*);

	void* data;
} libkv_t;


static inline void* libkv_get(libkv_t* x,
		const void* key, size_t keylen,
		size_t* result_vallen)
{
	return x->kv_get(x->data, key, keylen, result_vallen);
}

static inline bool libkv_del(libkv_t* x,
		const void* key, size_t keylen)
{
	return x->kv_del(x->data, key, keylen);
}

static inline bool libkv_put(libkv_t* x,
		const void* key, size_t keylen,
		const void* val, size_t vallen)
{
	return x->kv_put(x->data, key, keylen, val, vallen);
}

static inline libkv_mget_data* libkv_mget(libkv_t* x,
		char** keys, size_t* keylens, size_t num)
{
	libkv_mget_data* mx = (libkv_mget_data*)malloc(sizeof(libkv_mget_data));
	if(!x->kv_mget(x->data, mx, keys, keylens, num)) {
		free(mx);
		return NULL;
	}
	return mx;
}

static inline const void* libkv_mget_next(libkv_mget_data* mx,
		void* keybuf, size_t* keybuflen,
		size_t* result_vallen)
{
	return mx->kv_mget_next(mx->data, keybuf, keybuflen, result_vallen);
}

static inline void libkv_mget_free(libkv_mget_data* mx)
{
	mx->kv_mget_free(mx->data);
	free(mx);
}

static inline bool libkv_close(libkv_t* mx)
{
	return mx->kv_close(mx->data);
}

static inline const char* libkv_errmsg(libkv_t* mx)
{
	return mx->kv_errmsg(mx->data);
}


#ifdef __cplusplus
}
#endif

#endif /* libkv.h */


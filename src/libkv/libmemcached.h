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


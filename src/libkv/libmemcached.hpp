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
#ifndef LIBKV_LIBMEMCACHED_HPP__
#define LIBKV_LIBMEMCACHED_HPP__

#include "libkv.hpp"
#include "libkv/libmemcached.h"
#include <stdexcept>

namespace libkv {


class libmemcached : public base {
public:
	libmemcached()
	{
		if(!libkv_libmemcached_init(this)) {
			throw std::bad_alloc();
		}
	}

	bool add(const char* hostname, unsigned int port)
	{
		return libkv_libmemcached_add(
				this, hostname, port);
	}

	bool add_udp(const char* hostname, unsigned int port)
	{
		return libkv_libmemcached_add_udp(
				this, hostname, port);
	}
	
	bool add_unix_socket(const char* path)
	{
		return libkv_libmemcached_add_unix_socket(
				this, path);
	}
	
	bool add_list(const char* server_strings)
	{
		return libkv_libmemcached_add_list(
				this, server_strings);
	}
};


}  // namespace base

#endif /* libkv/libmemcached.hpp */


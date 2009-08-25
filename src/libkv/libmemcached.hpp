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


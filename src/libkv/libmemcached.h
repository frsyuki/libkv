#include <libmemcached/memcached.h>
#include "libkv.h"

/*
class libkv_libmemcached : public libkv {
public:
	libkv_libmemcached();

	int get(
			const void* key, size_t keylen,
			void* valbuf, size_t valbuflen);

	void* libkv_get_malloc(
			const void* key, size_t keylen,
			size_t* result_vallen);

	class multi : public libkv::multi {
	public:
		struct data {
			char* data;
			size_t size;
		};

		data* add(const void* key, size_t keylen);
		void submit();
	};

	multi* mget();
};
*/


int libkv_libmemcached_init();


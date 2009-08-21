#include "libkv/libmemcached.h"
#include <string.h>
#include <stdio.h>

#define check(cond, ...) \
	if(!(cond)) { fprintf(stderr, __VA_ARGS__); exit(1); }

int main(void)
{
	bool ret;
	void* data;
	size_t len;
	libkv kv;

	ret = libkv_libmemcached_init(&kv);
	check(ret, "init failed");

	ret = libkv_libmemcached_add(&kv, "127.0.0.1", 11211);
	check(ret, "failed to add 127.0.0.1:11211");

	ret = libkv_put(&kv, "k1", 2, "v1", 2);
	check(ret, "failed to put k1");

	data = libkv_get(&kv, "k1", 2, &len);
	check(ret, "failed to get k1");

	free(data);

	check(memcmp(data,"v1",2) == 0, "value of k1 mismatched");

	ret = libkv_del(&kv, "k1", 2);
	check(ret, "failed to del k1");

	ret = libkv_del(&kv, "k1", 2);
	check(!ret, "unexpectedly success to del k1");

	ret = libkv_close(&kv);
	check(ret, "failed to close");

	return 0;
}


#include "libkv/libmemcached.h"
#include <string.h>
#include <stdio.h>

#define check(cond, fmt, ...) \
	if(!(cond)) { fprintf(stderr, fmt "\n", ##__VA_ARGS__); exit(1); }

int main(void)
{
	bool ret;
	void* data;
	size_t len;
	libkv_t kv;

	ret = libkv_libmemcached_init(&kv);
	check(ret, "init failed");

	ret = libkv_libmemcached_add(&kv, "127.0.0.1", 11211);
	check(ret, "failed to add 127.0.0.1:11211: %s", libkv_errmsg(&kv));

	ret = libkv_put(&kv, "k1", 2, "v1", 2);
	check(ret, "failed to put k1");

	data = libkv_get(&kv, "k1", 2, &len);
	check(data, "failed to get k1");

	check(len == 2, "value size of k1 mismatched");
	check(memcmp(data,"v1",2) == 0, "value of k1 mismatched");

	free(data);

	ret = libkv_del(&kv, "k1", 2);
	check(ret, "failed to del k1");

	ret = libkv_del(&kv, "k1", 2);
	check(!ret, "unexpectedly success to del k1");

	int i;
	char* keys[] = { "k1", "k2", "k3" };
	size_t keylens[] = { 2, 2, 2 };
	for(i=0; i < 3; ++i) {
		libkv_put(&kv, keys[i], keylens[i], "val", 3);
	}

	libkv_mget_data* mdata = libkv_mget(&kv, keys, keylens, 3);
	check(mdata != NULL, "failed to mget");

	char keybuf[1024];
	size_t keybuflen;
	const void* cdata;

	for(i=0; i < 3; ++i) {
		keybuflen = sizeof(keybuf);
		cdata = libkv_mget_next(mdata, keybuf, &keybuflen, &len);
		check(cdata != NULL, "failed to mget next");
		check(len == 3, "invalid mget value size %lu", len);
		check(keybuflen == 2, "invalid mget key size %lu", keybuflen);
		check(memcmp(cdata, "val", 3) == 0, "invalid mget value");
	}

	libkv_mget_free(mdata);

	ret = libkv_close(&kv);
	check(ret, "failed to close");

	return 0;
}


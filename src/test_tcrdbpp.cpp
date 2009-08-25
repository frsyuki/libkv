#include "libkv/tcrdb.hpp"
#include <string.h>
#include <stdio.h>

#define check(cond, fmt, ...) \
	if(!(cond)) { fprintf(stderr, fmt "\n", ##__VA_ARGS__); exit(1); }

int main(void)
{
	bool ret;
	void* data;
	size_t len;

	libkv::tcrdb kv;

	ret = kv.open("127.0.0.1", 1978);
	check(ret, "failed to open 127.0.0.1:1978");

	ret = kv.put("k1", 2, "v1", 2);
	check(ret, "failed to put k1");

	data = kv.get("k1", 2, &len);
	check(ret, "failed to get k1");

	check(len == 2, "value size of k1 mismatched");
	check(memcmp(data,"v1",2) == 0, "value of k1 mismatched");

	free(data);

	ret = kv.del("k1", 2);
	check(ret, "failed to del k1");

	ret = kv.del("k1", 2);
	check(!ret, "unexpectedly success to del k1");

	int i;
	char* keys[] = { "k1", "k2", "k3" };
	size_t keylens[] = { 2, 2, 2 };
	for(i=0; i < 3; ++i) {
		kv.put(keys[i], keylens[i], "val", 3);
	}

	libkv::mget_data mdata;
	ret = kv.mget(&mdata, keys, keylens, 3);
	check(ret, "failed to mget");

	char keybuf[1024];
	size_t keybuflen;
	const void* cdata;

	for(i=0; i < 3; ++i) {
		keybuflen = sizeof(keybuf);
		cdata = mdata.next(keybuf, &keybuflen, &len);
		check(cdata != NULL, "failed to mget next");
		check(len == 3, "invalid mget value size %lu", len);
		check(keybuflen == 2, "invalid mget key size %lu", keybuflen);
		check(memcmp(cdata, "val", 3) == 0, "invalid mget value");
	}

	return 0;
}


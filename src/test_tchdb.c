#include "libkv/tchdb.h"
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

	ret = libkv_tchdb_init(&kv);
	check(ret, "init failed");

	ret = libkv_tchdb_open(&kv, "test_tchdb.tch", HDBOWRITER|HDBOCREAT);
	check(ret, "failed to create test_tchdb.tch");

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

	ret = libkv_close(&kv);
	check(ret, "failed to close");

	return 0;
}


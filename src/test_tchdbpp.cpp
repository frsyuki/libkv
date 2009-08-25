#include "libkv/tchdb.hpp"
#include <string.h>
#include <stdio.h>

#define check(cond, fmt, ...) \
	if(!(cond)) { fprintf(stderr, fmt "\n", ##__VA_ARGS__); exit(1); }

int main(void)
{
	bool ret;
	void* data;
	size_t len;

	libkv::tchdb kv("test_tchdb.tch", HDBOWRITER|HDBOCREAT);

	ret = kv.put("k1", 2, "v1", 2);
	check(ret, "failed to put k1");

	data = kv.get("k1", 2, &len);
	check(ret, "failed to get k1");

	free(data);

	check(memcmp(data,"v1",2) == 0, "value of k1 mismatched");

	ret = kv.del("k1", 2);
	check(ret, "failed to del k1");

	ret = kv.del("k1", 2);
	check(!ret, "unexpectedly success to del k1");

	return 0;
}


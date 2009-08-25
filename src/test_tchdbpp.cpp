#include "libkv/tchdb.hpp"
#include <string.h>
#include <stdio.h>

#define check(cond, fmt, ...) \
	if(!(cond)) { fprintf(stderr, fmt "\n", ##__VA_ARGS__); exit(1); }

int main(void)
{
	bool ret;
	std::string key;
	std::string val;

	libkv::tchdb kv;

	ret = kv.open("test_tchdb.tch", HDBOWRITER|HDBOCREAT);
	check(ret, "failed to create test_tchdb.tch");

	ret = kv.put("k1", "v1");
	check(ret, "failed to put k1");

	ret = kv.get("k1", &val);
	check(ret, "failed to get k1");

	check(val.size() == 2, "value size of k1 mismatched");
	check(val == "v1", "value of k1 mismatched");

	ret = kv.del("k1");
	check(ret, "failed to del k1");

	ret = kv.del("k1");
	check(!ret, "unexpectedly success to del k1");

	return 0;
}


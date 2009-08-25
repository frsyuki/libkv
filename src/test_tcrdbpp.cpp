#include "libkv/tcrdb.hpp"
#include <string.h>
#include <stdio.h>

#define check(cond, fmt, ...) \
	if(!(cond)) { fprintf(stderr, fmt "\n", ##__VA_ARGS__); exit(1); }

int main(void)
{
	bool ret;
	std::string key;
	std::string val;

	libkv::tcrdb kv;

	ret = kv.open("127.0.0.1", 1978);
	check(ret, "failed to open 127.0.0.1:1978");

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

	std::vector<std::string> keys;
	keys.push_back("k1");
	keys.push_back("k2");
	keys.push_back("k3");

	libkv::mget_data mdata;
	ret = kv.mget(&mdata, keys.begin(), keys.end());
	check(ret, "failed to mget");

	for(int i=0; i < 3; ++i) {
		ret = mdata.next(&key, &val);
		check(ret, "failed to mget next");
		check(val.size() == 3, "invalid mget value size %lu", val.size());
		check(key.size() == 2, "invalid mget key size %lu", key.size());
		check(val.substr(0,3) == "val", "invalid mget key size %lu", key.size());
	}

	return 0;
}


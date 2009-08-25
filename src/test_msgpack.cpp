#include <msgpack.hpp>
#include <iostream>
#include "libkv/tchdb.hpp"

#define check(cond, fmt, ...) \
	if(!(cond)) { fprintf(stderr, fmt "\n", ##__VA_ARGS__); exit(1); }

int main(void)
{
	bool ret;
	libkv::tchdb kv;

	ret = kv.open("test_tchdb.tch", HDBOWRITER|HDBOCREAT);

	int num = 1;

	std::vector<std::string> vec;
	vec.push_back("elem");

	ret = kv.put_obj("num", num);
	check(ret, "failed to put num");

	ret = kv.put_obj("vec", vec);
	check(ret, "failed to put vec");


	num = 0;
	vec.clear();

	ret = kv.get_obj("num", &num);
	check(ret, "failed to get num");
	check(num == 1, "num mismatched");

	ret = kv.get_obj("vec", &vec);
	check(ret, "failed to get vec");
	check(vec.size() == 1 && vec[0] == "elem", "vec mismatched");
}


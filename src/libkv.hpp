#ifndef LIBKV_HPP__
#define LIBKV_HPP__

#include "libkv.h"
#include <string>
#include <vector>
#include <stdlib.h>

namespace libkv {


class mget_data : public libkv_mget_data {
public:
	mget_data();
	~mget_data();

	const void* next(
			void* keybuf, size_t* keybuflen,
			size_t* result_vallen);

	bool next(
			std::string* result_key,
			std::string* result_value);

private:
	mget_data(const mget_data&);
};


class base : protected libkv_t {
protected:
	base();

public:
	~base();

	void* get(
		const void* key, size_t keylen,
		size_t* result_vallen);

	bool get(
		const std::string& key,
		std::string* result_value);

	bool put(
			const void* key, size_t keylen,
			const void* val, size_t vallen);

	bool put(
			const std::string& key,
			const std::string& value);

	bool del(
			const void* key, size_t keylen);

	bool del(
			const std::string& key);

	bool mget(mget_data* mx,
			char** keys, size_t* keylens, size_t num);

	template <typename StringForwardIterator>
	bool mget(mget_data* mx,
			StringForwardIterator begin, StringForwardIterator end);

private:
	base(const base&);
};


template <typename StringForwardIterator>
bool base::mget(mget_data* mx,
		StringForwardIterator begin, StringForwardIterator end)
{
	bool ok = false;
	std::vector<char*>  keys;
	std::vector<size_t> keylens;

	while(begin != end) {
		const char* data = begin->data();
		size_t size = begin->size();
		char* mem = (char*)malloc(size);
		if(mem == NULL) {
			goto out;
		}
		memcpy(mem, data, size);
		try {
			keylens.push_back(size);
			keys.push_back(mem);
		} catch (...) {
			goto out;
		}
		++begin;
	}

	ok = (*kv_mget)(this->data, mx, &keys[0], &keylens[0], keys.size());

out:
	for(std::vector<char*>::iterator it(keys.begin()),
			it_end(keys.end()); it != it_end; ++it) {
		free(*it);
	}
	return ok;
}


}  // namespace base

#endif /* libkv.hpp */


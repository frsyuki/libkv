#ifndef LIBKV_HPP__
#define LIBKV_HPP__

#include "libkv.h"
#include <string>

namespace libkv {


class mget_data : protected libkv_mget_data {
public:
	mget_data();
	~mget_data();

	const void* next(
			void* keybuf, size_t* keybuflen,
			size_t* result_vallen);
};


class base : protected libkv_t {
public:
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
	bool mget(mget_data*,
			StringForwardIterator begin, StringForwardIterator end);

private:
	base(const base&);
};


}  // namespace base

#endif /* libkv.hpp */


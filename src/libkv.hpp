/*
 * libkv
 *
 * Copyright (c) 2009 FURUHASHI Sadayuki
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef LIBKV_HPP__
#define LIBKV_HPP__

#include "libkv.h"
#include <string>
#include <vector>
#include <stdlib.h>
#include <string.h>

#ifdef LIBKV_MSGPACK
#include <msgpack.hpp>
#endif

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

#ifdef MSGPACK_OBJECT_HPP__
	template <typename T>
	bool next_obj(
			void* keybuf, size_t* keybuflen,
			T* result_obj);
#endif

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

#ifdef MSGPACK_OBJECT_HPP__
	template <typename T>
	bool put_obj(
			const void* key, size_t keylen,
			const T& obj);

	template <typename T>
	bool put_obj(
			const std::string& key,
			const T& obj);

	template <typename T>
	bool get_obj(
			const void* key, size_t keylen,
			T* result_obj);

	template <typename T>
	bool get_obj(
			const std::string& key,
			T* result_obj);
#endif

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


#ifdef MSGPACK_OBJECT_HPP__
template <typename T>
bool base::put_obj(
		const void* key, size_t keylen,
		const T& obj)
{
	msgpack::sbuffer sbuf;
	msgpack::pack(sbuf, obj);
	return put(key, keylen, sbuf.data(), sbuf.size());
}

template <typename T>
bool base::put_obj(
		const std::string& key,
		const T& obj)
{
	return put_obj<T>(key.data(), key.size(), obj);
}

template <typename T>
bool base::get_obj(
		const void* key, size_t keylen,
		T* result_obj)
{
	size_t vallen;
	void* val = get(key, keylen, &vallen);
	if(!val) {
		return false;
	}
	try {
		msgpack::zone z;
		msgpack::object obj;
		if(msgpack::unpack((const char*)val, vallen, NULL, &z, &obj) !=
				msgpack::UNPACK_SUCCESS) {
			throw msgpack::type_error();
		}
		obj.convert(result_obj);
		free(val);
		return true;
	} catch(...) {
		free(val);
		throw;
	}
}

template <typename T>
bool base::get_obj(
		const std::string& key,
		T* result_obj)
{
	return get_obj<T>(key.data(), key.size(), result_obj);
}

template <typename T>
bool mget_data::next_obj(
		void* keybuf, size_t* keybuflen,
		T* result_obj)
{
	size_t vallen;
	const void* val = next(keybuf, keybuflen, vallen);
	if(!val) {
		return false;
	}
	msgpack::zone z;
	msgpack::object obj;
	if(msgpack::unpack(val, vallen, NULL, &z, &obj) !=
			msgpack::UNPACK_SUCCESS) {
		throw msgpack::type_error();
	}
	obj.convert(result_obj);
	return true;
}
#endif


}  // namespace base

#endif /* libkv.hpp */


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
#include "libkv.hpp"

namespace libkv {


base::base()
{
	memset(this, 0, sizeof(base));
}

base::~base()
{
	if(kv_close) {
		(*kv_close)(this->data);
	}
}

void* base::get(
	const void* key, size_t keylen,
	size_t* result_vallen)
{
	return libkv_get(this, key, keylen, result_vallen);
}


bool base::get(
	const std::string& key,
	std::string* result_value)
{
	size_t vallen;
	void* val = get(key.data(), key.size(), &vallen);
	if(!val) {
		return false;
	}
	try {
		result_value->assign((char*)val, vallen);
		free(val);
		return true;
	} catch(...) {
		free(val);
		throw;
	}
}

bool base::put(
		const void* key, size_t keylen,
		const void* val, size_t vallen)
{
	return libkv_put(this, key, keylen, val, vallen);
}

bool base::put(
		const std::string& key,
		const std::string& value)
{
	return put(key.data(), key.size(), value.data(), value.size());
}

bool base::del(
		const void* key, size_t keylen)
{
	return libkv_del(this, key, keylen);
}

bool base::del(
		const std::string& key)
{
	return del(key.data(), key.size());
}

bool base::mget(mget_data* mx,
		char** keys, size_t* keylens, size_t num)
{
	return (*kv_mget)(this->data, mx, keys, keylens, num);
}


mget_data::mget_data()
{
	memset(this, 0, sizeof(mget_data));
}

mget_data::~mget_data()
{
	if(kv_mget_free) {
		(*kv_mget_free)(this->data);
	}
}

const void* mget_data::next(
		void* keybuf, size_t* keybuflen,
		size_t* result_vallen)
{
	return libkv_mget_next(this, keybuf, keybuflen, result_vallen);
}

bool mget_data::next(
		std::string* result_key,
		std::string* result_value)
{
	char kbuf[1024];
	size_t kbuflen = sizeof(kbuf);
	size_t vallen;
	const void* val = next(kbuf, &kbuflen, &vallen);
	if(val) {
		result_value->assign((char*)val, vallen);
		result_key->assign(kbuf, kbuflen);
		return true;
	}
	return false;
}


}  // namespace base


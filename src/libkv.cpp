#include "libkv.hpp"

namespace libkv {


base::base() { }

base::~base()
{
	(*kv_close)(this);
}

void* base::get(
	const void* key, size_t keylen,
	size_t* result_vallen)
{
	return (*kv_get)(this, key, keylen, result_vallen);
}


bool base::get(
	const std::string& key,
	std::string* result_value)
{
	size_t vallen;
	void* val = get(key.data(), key.size(), &vallen);
	if(val) try {
		result_value->assign((char*)val, vallen);
		free(val);
		return true;
	} catch(...) {
		free(val);
		throw;
	}
	return true;
}

bool base::put(
		const void* key, size_t keylen,
		const void* val, size_t vallen)
{
	return (*kv_put)(this, key, keylen, val, vallen);
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
	return (*kv_del)(this, key, keylen);
}

bool base::del(
		const std::string& key)
{
	return del(key.data(), key.size());
}

bool base::mget(mget_data* mx,
		char** keys, size_t* keylens, size_t num)
{
	return (*kv_mget)(this, (libkv_mget_data*)mx, keys, keylens, num);
}


mget_data::mget_data()
{
	memset(this, 0, sizeof(mget_data));
}

mget_data::~mget_data()
{
	if(kv_mget_free) {
		(*kv_mget_free)(this);
	}
}

const void* mget_data::next(
		void* keybuf, size_t* keybuflen,
		size_t* result_vallen)
{
	return (*kv_mget_next)(this, keybuf, keybuflen, result_vallen);
}


}  // namespace base


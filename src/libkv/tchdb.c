#include "libkv/tchdb.h"

static void* kv_get(TCHDB* c,
		const void* key, size_t keylen,
		size_t* result_vallen)
{
	int vallen = 0;
	void* val = tchdbget(c, key, keylen, &vallen);
	*result_vallen = vallen;
	return val;
}

static bool kv_put(TCHDB* c,
		const void* key, size_t keylen,
		const void* val, size_t vallen)
{
	return tchdbput(c, key, keylen, val, vallen);
}

static bool kv_del(TCHDB* c,
		const void* key, size_t keylen)
{
	return tchdbout(c, key, keylen);
}

static bool kv_close(TCHDB* c)
{
	bool r = tchdbclose(c);
	tchdbdel(c);
	return r;
}


bool libkv_tchdb_init(libkv_t* x)
{
	TCHDB* c = tchdbnew();
	if(!c) {
		return false;
	}
	if(!tchdbsetmutex(c)) {
		tchdbdel(c);
		return false;
	}
	x->kv_get   = (void*)&kv_get;
	x->kv_put   = (void*)&kv_put;
	x->kv_del   = (void*)&kv_del;
	x->kv_mget  = NULL;
	x->kv_close = (void*)&kv_close;
	x->data     = (void*)c;
	return true;
}

bool libkv_tchdb_open(libkv_t* x,
		const char* path, int mode)
{
	TCHDB* c = x->data;
	return tchdbopen(c, path, mode);
}


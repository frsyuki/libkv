#include "libkv/tcbdb.h"

static void* kv_get(TCBDB* c,
		const void* key, size_t keylen,
		size_t* result_vallen)
{
	int vallen = 0;
	void* val = tcbdbget(c, key, keylen, &vallen);
	*result_vallen = vallen;
	return val;
}

static bool kv_put(TCBDB* c,
		const void* key, size_t keylen,
		const void* val, size_t vallen)
{
	return tcbdbput(c, key, keylen, val, vallen);
}

static bool kv_del(TCBDB* c,
		const void* key, size_t keylen)
{
	return tcbdbout(c, key, keylen);
}

static bool kv_close(TCBDB* c)
{
	bool r = tcbdbclose(c);
	tcbdbdel(c);
	return r;
}


bool libkv_tcbdb_init(libkv_t* x)
{
	TCBDB* c = tcbdbnew();
	if(!c) {
		return false;
	}
	if(!tcbdbsetmutex(c)) {
		tcbdbdel(c);
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

bool libkv_tcbdb_open(libkv_t* x,
		const char* path, int mode)
{
	TCBDB* c = x->data;
	return tcbdbopen(c, path, mode);
}


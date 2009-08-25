#include "libkv/tcadb.h"

static void* kv_get(TCADB* c,
		const void* key, size_t keylen,
		size_t* result_vallen)
{
	int vallen = 0;
	void* val = tcadbget(c, key, keylen, &vallen);
	*result_vallen = vallen;
	return val;
}

static bool kv_put(TCADB* c,
		const void* key, size_t keylen,
		const void* val, size_t vallen)
{
	return tcadbput(c, key, keylen, val, vallen);
}

static bool kv_del(TCADB* c,
		const void* key, size_t keylen)
{
	return tcadbout(c, key, keylen);
}

static bool kv_close(TCADB* c)
{
	bool r = tcadbclose(c);
	tcadbdel(c);
	return r;
}


bool libkv_tcadb_init(libkv_t* x)
{
	TCADB* c = tcadbnew();
	if(!c) {
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

bool libkv_tcadb_open(libkv_t* x,
		const char* name)
{
	TCADB* c = x->data;
	return tcadbopen(c, name);
}


#include "libkv/tcrdb.h"

static void* kv_get(TCRDB* c,
		const void* key, size_t keylen,
		size_t* result_vallen)
{
	int vallen = 0;
	void* val = tcrdbget(c, key, keylen, &vallen);
	*result_vallen = vallen;
	return val;
}

static bool kv_put(TCRDB* c,
		const void* key, size_t keylen,
		const void* val, size_t vallen)
{
	return tcrdbput(c, key, keylen, val, vallen);
}

static bool kv_del(TCRDB* c,
		const void* key, size_t keylen)
{
	return tcrdbout(c, key, keylen);
}

static bool kv_close(TCRDB* c)
{
	bool r = tcrdbclose(c);
	tcrdbdel(c);
	return r;
}


/*
typedef struct kv_mget {
	TCLIST* list;
	TCMAP* map;
};

static libkv_data* kv_mget_add(TCMAP* mx,
		const void* key, size_t keylen)
{
	char* inlist;
	char* kbuf = malloc( keylen + sizeof(libkv_data) );
	if(kbuf == NULL) { return NULL; }

	libkv_data* data = kbuf + keylen;
	data->data = NULL;
	data->size = 0;

	if(!tclistunshift(mx->list, kbuf, keylen)) {
		free(kbuf);
		return NULL;
	}
	free(kbuf);

	inlist = tclistval(mx->list, 0, &keylen);
	if(!inlist) {
		return NULL;
	}

	return (libkv_data*)(inlist + keylen);
}
*/

static libkv_mget* kv_mget_new(TCRDB* c)
{
	return NULL;
}


bool libkv_tcrdb_init(libkv* x)
{
	TCRDB* c = tcrdbnew();
	if(!c) {
		return false;
	}
	x->kv_get      = (void*)&kv_get;
	x->kv_put      = (void*)&kv_put;
	x->kv_del      = (void*)&kv_del;
	x->kv_mget_new = (void*)&kv_mget_new;
	x->kv_close    = (void*)&kv_close;
	x->data        = (void*)c;
	return true;
}

bool libkv_tcrdb_open(libkv* x,
		const char* path, int mode)
{
	TCRDB* c = x->data;
	return tcrdbopen(c, path, mode);
}


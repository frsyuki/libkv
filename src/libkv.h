#include <stddef.h>
#include <stdbool.h>

typedef struct libkv_data {
	char* data;
	size_t size;
} libkv_data;


typedef struct libkv_mget {
	libkv_data* (*kv_mget_add)(void*,
			const char* key, size_t keylen);

	bool (*kv_mget_submit)(void*);

	void (*kv_mget_free)(void*);

	void* data;
} libkv_mget;


typedef struct libkv {
	void* (*kv_get)(void*,
		const void* key, size_t keylen,
		size_t* result_vallen);

	bool (*kv_put)(void*,
			const void* key, size_t keylen,
			const void* val, size_t vallen);

	bool (*kv_del)(void*,
			const void* key, size_t keylen);

	libkv_mget* (*kv_mget_new)(void*);

	bool (*kv_close)(void*);

	void* data;
} libkv;


static inline void* libkv_get(libkv* x,
		const void* key, size_t keylen,
		size_t* result_vallen)
{
	return x->kv_get(x->data, key, keylen, result_vallen);
}

static inline bool libkv_del(libkv* x,
		const void* key, size_t keylen)
{
	return x->kv_del(x->data, key, keylen);
}

static inline bool libkv_put(libkv* x,
		const void* key, size_t keylen,
		const void* val, size_t vallen)
{
	return x->kv_put(x->data, key, keylen, val, vallen);
}

static inline libkv_mget* libkv_mget_new(libkv* x)
{
	return x->kv_mget_new(x->data);
}

static inline libkv_data* libkv_mget_add(libkv_mget* mx,
		const char* key, size_t keylen)
{
	return mx->kv_mget_add(mx->data, key, keylen);
}

static inline bool libkv_mget_submit(libkv_mget* mx)
{
	return mx->kv_mget_submit(mx->data);
}

static inline void libkv_mget_free(libkv_mget* mx)
{
	mx->kv_mget_free(mx);
}

static inline bool libkv_close(libkv* mx)
{
	return mx->kv_close(mx->data);
}



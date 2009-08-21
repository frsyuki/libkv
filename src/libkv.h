#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct libkv_mget_data {
	const void* (*kv_mget_next)(void*,
			void* keybuf, size_t* keybuflen,
			size_t* result_vallen);

	void (*kv_mget_free)(void*);

	void* data;
} libkv_mget_data;


typedef struct libkv {
	void* (*kv_get)(void*,
		const void* key, size_t keylen,
		size_t* result_vallen);

	bool (*kv_put)(void*,
			const void* key, size_t keylen,
			const void* val, size_t vallen);

	bool (*kv_del)(void*,
			const void* key, size_t keylen);

	bool (*kv_mget)(void*, libkv_mget_data*,
			char** keys, size_t* keylens, size_t num);

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

static inline libkv_mget_data* libkv_mget(libkv* x,
		char** keys, size_t* keylens, size_t num)
{
	libkv_mget_data* mx = malloc(sizeof(libkv_mget_data));
	if(!x->kv_mget(x->data, mx, keys, keylens, num)) {
		free(mx);
		return NULL;
	}
	return mx;
}

static inline const void* libkv_mget_next(libkv_mget_data* mx,
		void* keybuf, size_t* keybuflen,
		size_t* result_vallen)
{
	return mx->kv_mget_next(mx->data, keybuf, keybuflen, result_vallen);
}

static inline void libkv_mget_free(libkv_mget_data* mx)
{
	mx->kv_mget_free(mx->data);
	free(mx);
}

static inline bool libkv_close(libkv* mx)
{
	return mx->kv_close(mx->data);
}


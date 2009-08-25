#ifndef LIBKV_TCHDB_H__
#define LIBKV_TCHDB_H__

#include "libkv.h"
#include <tchdb.h>

#ifdef __cplusplus
extern "C" {
#endif

bool libkv_tchdb_init(libkv_t*);

bool libkv_tchdb_open(libkv_t*, const char* path, int mode);


#ifdef __cplusplus
}
#endif

#endif /* libkv/tchdb.h */


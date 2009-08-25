#ifndef LIBKV_TCADB_H__
#define LIBKV_TCADB_H__

#include "libkv.h"
#include <tcadb.h>

#ifdef __cplusplus
extern "C" {
#endif

bool libkv_tcadb_init(libkv_t*);

bool libkv_tcadb_open(libkv_t*, const char* name);


#ifdef __cplusplus
}
#endif

#endif /* libkv/tcadb.h */


#ifndef LIBKV_TCBDB_H__
#define LIBKV_TCBDB_H__

#include "libkv.h"
#include <tcbdb.h>

#ifdef __cplusplus
extern "C" {
#endif

bool libkv_tcbdb_init(libkv_t*);

bool libkv_tcbdb_open(libkv_t*, const char* path, int mode);


#ifdef __cplusplus
}
#endif

#endif /* libkv/tcbdb.h */


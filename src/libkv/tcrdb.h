#ifndef LIBKV_TCRDB_H__
#define LIBKV_TCRDB_H__

#include "libkv.h"
#include <tcrdb.h>

#ifdef __cplusplus
extern "C" {
#endif


bool libkv_tcrdb_init(libkv_t*);

bool libkv_tcrdb_open(libkv_t*, const char* host, int port);


#ifdef __cplusplus
}
#endif

#endif /* libkv/tcrdb.h */


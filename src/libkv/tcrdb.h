#include "libkv.h"
#include <tcrdb.h>

bool libkv_tcrdb_init(libkv*);

bool libkv_tcrdb_open(libkv*, const char* path, int mode);


#include "libkv.h"
#include <tchdb.h>

bool libkv_tchdb_init(libkv*);

bool libkv_tchdb_open(libkv*, const char* path, int mode);


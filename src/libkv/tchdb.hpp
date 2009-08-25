#ifndef LIBKV_TCHDB_HPP__
#define LIBKV_TCHDB_HPP__

#include "libkv.hpp"
#include "libkv/tchdb.h"
#include <stdexcept>

namespace libkv {


class tchdb : public base {
public:
	tchdb(const char* path, int mode)
	{
		if(!libkv_tchdb_open((libkv_t*)this, path, mode)) {
			throw std::runtime_error("failed to open libkv::tchdb");
		}
	}
};


}  // namespace base

#endif /* libkv/tchdb.hpp */


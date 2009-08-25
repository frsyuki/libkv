#ifndef LIBKV_TCHDB_HPP__
#define LIBKV_TCHDB_HPP__

#include "libkv.hpp"
#include "libkv/tchdb.h"
#include <stdexcept>

namespace libkv {


class tchdb : public base {
public:
	tchdb()
	{
		if(!libkv_tchdb_init(this)) {
			throw std::bad_alloc();
		}
	}

	bool open(const char* path, int mode)
	{
		return libkv_tchdb_open(this, path, mode);
	}
};


}  // namespace base

#endif /* libkv/tchdb.hpp */


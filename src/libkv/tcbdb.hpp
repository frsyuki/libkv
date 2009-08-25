#ifndef LIBKV_TCBDB_HPP__
#define LIBKV_TCBDB_HPP__

#include "libkv.hpp"
#include "libkv/tcbdb.h"
#include <stdexcept>

namespace libkv {


class tcbdb : public base {
public:
	tcbdb()
	{
		if(!libkv_tcbdb_init(this)) {
			throw std::bad_alloc();
		}
	}

	bool open(const char* path, int mode)
	{
		return libkv_tcbdb_open(this, path, mode);
	}
};


}  // namespace base

#endif /* libkv/tcbdb.hpp */


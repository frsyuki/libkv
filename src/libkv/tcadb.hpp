#ifndef LIBKV_TCADB_HPP__
#define LIBKV_TCADB_HPP__

#include "libkv.hpp"
#include "libkv/tcadb.h"
#include <stdexcept>

namespace libkv {


class tcadb : public base {
public:
	tcadb()
	{
		if(!libkv_tcadb_init(this)) {
			throw std::bad_alloc();
		}
	}

	bool open(const char* name)
	{
		return libkv_tcadb_open(this, name);
	}
};


}  // namespace base

#endif /* libkv/tcadb.hpp */


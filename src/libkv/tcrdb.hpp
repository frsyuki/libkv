#ifndef LIBKV_TCRDB_HPP__
#define LIBKV_TCRDB_HPP__

#include "libkv.hpp"
#include "libkv/tcrdb.h"
#include <stdexcept>

namespace libkv {


class tcrdb : public base {
public:
	tcrdb()
	{
		if(!libkv_tcrdb_init(this)) {
			throw std::bad_alloc();
		}
	}

	bool open(const char* host, int port)
	{
		return libkv_tcrdb_open(this, host, port);
	}
};


}  // namespace base

#endif /* libkv/tcrdb.hpp */


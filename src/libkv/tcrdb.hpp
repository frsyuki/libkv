#ifndef LIBKV_TCRDB_HPP__
#define LIBKV_TCRDB_HPP__

#include "libkv.hpp"
#include "libkv/tcrdb.h"
#include <stdexcept>

namespace libkv {


class tcrdb : public base {
public:
	tcrdb(const char* host, int port)
	{
		if(!libkv_tcrdb_open((libkv_t*)this, host, port)) {
			throw std::runtime_error("failed to open libkv::tcrdb");
		}
	}
};


}  // namespace base

#endif /* libkv/tcrdb.hpp */


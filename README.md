libkv
=====

## Overview

libkv is an abstraction library for various key-value stores.
It supports following key-value stores:

  - Tokyo Cabinet
  - Tokyo Tyrant
  - memcached


## Installation

Configure and install in the usual way:

    $ ./bootstrap  # if needed
    $ ./configure
    $ make
    $ sudo make install

### Configuration flags

**--disable-tc** Disable Tokyo Cabinet support

**--disable-tt** Disable Tokyo Tyorant support

**--disable-libmemcached** Disable libmemcached support


## Usage

### C API
Include libkv/IMPL.h header and link libkv library.
IMPL is one of libmemcached, tcadb, tcbdb, tchdb or tcrdb.

See src/test_libmemcached.c or src/test_tchdb.c for example.

### C++ API
Include libkv/IMPL.hpp header and link libkvpp library.
IMPL is one of libmemcached, tcadb, tcbdb, tchdb or tcrdb.

See src/test_tcrdbpp.cpp or src/test_msgpack.cpp for example.

To use put_obj and get_obj APIs, include msgpack.hpp header before including
libkv header or add -DLIBKV_MSGPACK flag to CXXFLAGS.


## License

    Copyright (c) 2009 FURUHASHI Sadayuki
    
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    
    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

See also NOTICE file.


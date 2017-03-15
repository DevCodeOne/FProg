#! /bin/bash
export CXX="cc_args.py g++"
exec cmake -DCMAKE_BUILD_TYPE=Debug .

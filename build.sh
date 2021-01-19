#!/usr/bin/env bash

cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS_DEBUG="-g" -Hjdong -Bbuild/jdong
cmake --build build/jdong

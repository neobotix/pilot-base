#!/bin/bash

mkdir -p build

cd build

if [ `uname -o` == "Msys" ]; then
	cmake -G "MSYS Makefiles" -D CMAKE_CXX_FLAGS="-O3" $@ ..
else
	cmake -D CMAKE_CXX_FLAGS="-O3" $@ ..
fi

make -j8 install


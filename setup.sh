#!/bin/sh

if [ $1 = "init" ]
then
git submodule update --init --recursive
cd thirdparty/boost
./bootstrap.sh
./b2 headers
cd ../..
fi

if [ $1 = "release" ]
then
cd build && cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..
make
cd ..
fi

if [ $1 = "debug" ]
then
cd build && cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
make
cd ..
fi

if [ $1 = "clean" ]
then
rm -r build/*
rm -r bin/*
fi
#!/usr/bin/bash

if [ ! -d "Release/" ]
then
    mkdir Release
    cd Release/
    cmake -DCMAKE_BUILD_TYPE=Release ..
    cd ../
fi

cd Release/ &&
make &&
cd bin/ &&
./e6502 &&
cd ../../
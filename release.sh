#!/usr/bin/bash

if [ ! -d "Release/" ]
then
    mkdir Release
    cd Release/
    cmake -DCMAKE_BUILD_TYPE=Release ..
    cd ../
fi

cd rom && 
vasm6502_oldstyle -Fbin -dotdir rom.s -o rom.bin &&
cd ../ &&
rm -rf Release/bin/rom && 
cp -r rom/ Release/bin/rom

cd Release/ &&
make &&
cd bin/ &&
./e6502 rom/rom.bin &&
cd ../../
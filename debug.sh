#!/usr/bin/bash

if [ ! -d "Debug/" ]
then
    mkdir Debug
    cd Debug/
    cmake -DCMAKE_BUILD_TYPE=Debug ..
    cd ../
fi

cd rom && 
vasm6502_oldstyle -Fbin -dotdir rom.s -o rom.bin &&
cd ../ &&
rm -rf Debug/bin/rom && 
cp -r rom/ Debug/bin/rom

cd Debug/ &&
make &&
cd bin/ &&
./e6502 rom/rom.bin &&
cd ../../
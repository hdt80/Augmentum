@echo off
cd Lua-build
make -s
cp lib/*.a ../../lib
cp lib/*.dll ../../bin
cd ../..

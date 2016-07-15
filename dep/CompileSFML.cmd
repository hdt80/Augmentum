@echo off
cd SFML-build
make -s
cp lib/*.a ../../lib
cp lib/*.dll ../../bin
cd ../..

@echo off
cd SFML-build
make -s
copy lib/*.a ../../lib
copy lib/*.dll ../../bin
cd ../..

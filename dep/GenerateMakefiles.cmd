@echo off
if exist SFML-build (
	echo Build dir exists, removing...
	rmdir /s /q SFML-build
)
if exist Lua-build (
	echo Lua build dir exists, removing...
	rmdir /s /q Lua-build
)
cmake -BSFML-build -HSFML -G "MinGW Makefiles" 
cmake -BLua-build -HLua -G "MinGW Makefiles"

@echo off
if exist SFML-build (
	echo Build dir exists, removing...
	rmdir /s /q SFML-build
)
cmake -BSFML-build -HSFML -G "MinGW Makefiles" 
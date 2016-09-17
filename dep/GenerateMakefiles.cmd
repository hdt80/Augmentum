@echo off
if exist SFML-build (
	echo Build dir exists, removing...
	rmdir /s /q SFML-build
)

if exist box2d-build (
    echo Box2D build dir exists, removing...
    rmdir /s /q box2d-build
)

cmake -Bbox2d-build -Hbox2d -G "MinGW Makefiles"
cmake -BSFML-build -HSFML -G "MinGW Makefiles" 

BOX2D_BUILD_DIR="Box2D-build"
SFML_BUILD_DIR="SFML-build"

if [ -d "$BOX2D_BUILD_DIR" ];
then
	echo Box2D-build exists, removing...
	rm Box2D-build -r
	mkdir Box2D-build
else
	echo Box2D-build not found
fi

if [ -d "$SFML_BUILD_DIR" ];
then
	echo SFML-build exists, removing...
	rm SFML-build -r
	mkdir SFML-build
else
	echo SFML-build not found
fi

cmake -BBox2D-build -Hbox2d -G "Unix Makefiles"
cmake -BSFML-build -HSFML -G "Unix Makefiles"

if [ -f Box2D-build ];
then
	rm Box2D-build -r
	mkdir Box2D-build
fi

if [ -f SFML-build ];
then
	rm SFML-build -r
	mkdir SFML-build
fi

cmake -BBox2D-build -Hbox2d -G "Unix Makefiles"
cmake -BSFML-build -HSFML -G "Unix Makefiles"

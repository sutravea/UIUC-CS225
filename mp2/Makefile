FLAGS = -g -O0 -Wall -std=c++11

all: testimage testscene

testimage: testimage.o image.o png.o rgbapixel.o
	g++ $(FlAGS) testimage.o image.o png.o rgbapixel.o -lpng -o testimage

testscene: testscene.o image.o scene.o png.o rgbapixel.o
	g++ $(FLAGS) testscene.o image.o scene.o png.o rgbapixel.o -lpng -o testscene

testscene.o: testscene.cpp
	g++ $(FLAGS) -c testscene.cpp

scene.o: scene.cpp
	g++ $(FLAGS) -c scene.cpp

testimage.o: testimage.cpp
	g++ $(FlAGS) -c testimage.cpp

rgbapixel.o: rgbapixel.cpp
	g++ $(FlAGS) -c rgbapixel.cpp

png.o: png.cpp rgbapixel.cpp
	g++ $(FlAGS) -c png.cpp rgbapixel.cpp -lpng

image.o: image.cpp png.cpp
	g++ $(FlAGS) -c image.cpp png.cpp

clean:
	rm *o testimage


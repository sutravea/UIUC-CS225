FLAGS = -g -O0 -Wall

all: testimage

testimage: testimage.o rgbapixel.o png.o image.o
	g++ $(FlAGS) testimage.o png.o rgbapixel.o image.o -lpng -o testimage

testimage.o: testimage.cpp
	g++ $(FlAGS) -c testimage.cpp

rgbapixel.o: rgbapixel.cpp
	g++ $(FlAGS) -c rgbapixel.cpp

png.o: png.cpp
	g++ $(FlAGS) -c png.cpp -lpng

image.o: image.cpp
	g++ $(FlAGS) -c image.cpp

clean:
	rm -*o testimage


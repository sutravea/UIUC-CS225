all: mp1

mp1: main.o rgbapixel.o png.o
	g++ main.o png.o rgbapixel.o -lpng -o mp1

main.o: main.cpp
	g++ -c main.cpp

rgbapixel.o: rgbapixel.cpp
	g++ -c rgbapixel.cpp

png.o: png.cpp
	g++ -c png.cpp -lpng

clean:
	rm -rf *o mp1


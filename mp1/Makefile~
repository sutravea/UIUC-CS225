all: blah

blah: main.o sphere.o
	g++ main.o sphere.o -o bleh

main.o: main.cpp
	g++ -c main.cpp

sphere.o: sphere.cpp
	g++ -c sphere.cpp

clean:
	rm -rf *o bleh


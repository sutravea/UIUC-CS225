EXENAME = example1

COMPILER = g++ 
COMPILER_OPTS = -c -g -O0 # -Werror-all
LINKER = g++ -lpng

MAIN_OBJS = point.o rgbapixel.o png.o collage.o main.o

all: $(EXENAME)

$(EXENAME) : $(MAIN_OBJS) images soln_collage.png
	$(LINKER) $(MAIN_OBJS) -o $(EXENAME)

main.o : png.o collage.o main.cpp
	$(COMPILER) $(COMPILER_OPTS) main.cpp

collage.o : point.o png.o collage.h collage.cpp
	$(COMPILER) $(COMPILER_OPTS) collage.cpp

png.o : png.h png.cpp rgbapixel.o
	$(COMPILER) $(COMPILER_OPTS) png.cpp

rgbapixel.o : rgbapixel.h rgbapixel.cpp
	$(COMPILER) $(COMPILER_OPTS) rgbapixel.cpp

point.o : point.h point.cpp
	$(COMPILER) $(COMPILER_OPTS) point.cpp

images :
	svn export https://subversion.ews.illinois.edu/svn/fa12-cs225/_shared/lab_race/images/

soln_collage.png :
	svn export https://subversion.ews.illinois.edu/svn/fa12-cs225/_shared/lab_race/soln_collage.png

clean:
	-rm -f *.o $(EXENAME)

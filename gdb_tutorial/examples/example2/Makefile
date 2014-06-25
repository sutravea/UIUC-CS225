EXENAME = example2

COMPILER = g++ 
COMPILER_OPTS = -c -g -O0 # -Werror-all
LINKER = g++

MAIN_OBJS = main.o

all: $(EXENAME)

$(EXENAME) : $(MAIN_OBJS)
	$(LINKER) $(MAIN_OBJS) -o $(EXENAME)

main.o : main.cpp
	$(COMPILER) $(COMPILER_OPTS) main.cpp

clean :
	-rm -f *.o $(EXENAME)

CC = g++
CFLAGS = -Wall -Wshadow
EXENAME = pure-monad
CCMONAD = cc-monad
OBJS = monad.o help.o util.o filemap.o monad_shared.o
CCOBJS = ccmonad.o util.o monad_shared.o
IDFILE = ../.monadid
OPTIMIZE = off

ifeq ($(strip $(OPTIMIZE)),on)
CFLAGS += -O2 -DOPTIMIZE
else ifeq ($(strip $(OPTIMIZE)),off)
CFLAGS += -g -O0
else
$(warning Invalid value specified for OPTIMIZE. Should be on or off)
CFLAGS += -g -O0
endif

LIBS:=
IS_LIBRT:=$(shell echo "int main(){}" | g++ -o /dev/null -x c++ - -lrt &>/dev/null ; echo $$?)
IS_LIBPNG:=$(shell echo "int main(){}" | g++ -o /dev/null -x c++ - -lpng &>/dev/null ; echo $$?)
ifeq ($(IS_LIBRT),0)
LIBS+= -lrt
endif
ifeq ($(IS_LIBPNG),0)
LIBS+= -lpng 
endif

.PHONY: monad
monad: $(EXENAME) $(CCMONAD) $(IDFILE)
.PHONY: all
all: monad

$(IDFILE): $(OBJS)
	echo -e '$(EXENAME) identification file\n'\
'This file is used for $(EXENAME) directory identification\n'\
'Built by' `whoami` 'on' `hostname`'\n'\
'Build Date:' `date`> $(IDFILE)

$(EXENAME): $(OBJS) $(IDFILE)
	$(CC) $(LIBS) $(CFLAGS) $(OBJS) -o $@

$(CCMONAD): $(CCOBJS) $(IDFILE)
	$(CC) $(LIBS) $(CFLAGS) $(CCOBJS) -o $@

help.o: help.cpp $(wildcard *.h) README.cgo README_config.cgo README_tests.cgo LICENSE.cgo quotes.cga

CONVERT_TXT_TO_CGO=sed -e 's/"/\\"/g' -e 's/^/    << "/' -e 's/$$/" << endl/'
CONVERT_TXT_TO_CGA=sed -e 's/"/\\"/g' -e 's/^/"/' -e 's/$$/",/'

%.cgo: %.txt
	$(CONVERT_TXT_TO_CGO) $(@:.cgo=.txt) > $@

%.cga: %.txt
	$(CONVERT_TXT_TO_CGA) $(@:.cga=.txt) > $@

%.o : %.cpp $(wildcard *.h)
	$(CC) $(CFLAGS) -c $(@:.o=.cpp) -o $@

.PHONY: clean
clean:
	rm -f $(wildcard *.o) $(wildcard *.cgo) $(wildcard *.cga) $(EXENAME) $(CCMONAD) $(IDFILE)


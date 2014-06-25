# This will force machines on EWS to use a modern g++ instead of the default
# (for C++11 support).
EWS_MODERN_CXX = /software/gcc-4.8.2/bin/g++
FALLBACK_CXX = g++
ifneq ($(wildcard $(EWS_MODERN_CXX)),) 
	CXX = $(EWS_MODERN_CXX)
	LDFLAGS = -static-libstdc++
else 
	CXX = $(FALLBACK_CXX)
	LDFLAGS = 
endif

#OPT = -O0

WARNINGS = -Wall -Wextra -pedantic
CXXFLAGS = -c -g -std=c++11 $(WARNINGS) 
DICT_RACER_OBJS = dict_racer.o
TEST_BTREE_OBJS = test_btree.o
EXES = dict_racer test_btree
RESULT_DIR = results

all: $(EXES)

$(RESULT_DIR):
	@mkdir -p $@

test_btree : $(TEST_BTREE_OBJS)
	$(CXX) $(LDFLAGS) $^ -o $@

dict_racer : $(DICT_RACER_OBJS) | $(RESULT_DIR)
	$(CXX) $(LDFLAGS) -O3 $^ -o $@

dict_racer.o : dict_racer.cpp btree.h btree.cpp btree_given.cpp benchmark.h
	$(CXX) $(CXXFLAGS) -O3 $< -o $@

test_btree.o : test_btree.cpp btree.h btree.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -rf $(EXES) $(TEST_BTREE_OBJS) $(DICT_RACER_OBJS) $(RESULT_DIR)



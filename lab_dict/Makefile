# This will force machines on EWS to use a modern g++ instead of the default
# (for C++11 support).
EWS_MODERN_CPPC = /software/gcc-4.8.2/bin/g++
FALLBACK_CPPC = g++
LDFLAGS =
ifneq ($(wildcard $(EWS_MODERN_CPPC)),) 
	CPPC = $(EWS_MODERN_CPPC)
	LDFLAGS = -static-libstdc++
else 
	CPPC = $(FALLBACK_CPPC)
	LDFLAGS = 
endif

WARNINGS = -Wall -Wextra -pedantic
CPPCFLAGS = -c -g -O0 -std=c++11 $(WARNINGS) 
OBJ_DIR = obj
ANAGRAM_OBJS = $(patsubst %.o, $(OBJ_DIR)/%.o, anagram_finder.o anagram_dict.o)
FIB_OBJS = $(patsubst %.o, $(OBJ_DIR)/%.o, fib.o fib_generator.o)
FAC_OBJS = $(patsubst %.o, $(OBJ_DIR)/%.o, fac.o)
GAME_OBJS = $(patsubst %.o, $(OBJ_DIR)/%.o, game.o game_test.o)
HOMOPHONE_OBJS = $(patsubst %.o, $(OBJ_DIR)/%.o, homophone_puzzle.o pronounce_dict.o cartalk_puzzle.o)
EXES = anagram_finder fib_generator fac game_test homophone_puzzle

all: $(EXES)

$(OBJ_DIR):
	@mkdir -p $@

anagram_finder: $(ANAGRAM_OBJS)
	$(CPPC) $(LDFLAGS) $^ -o $@

fib_generator: $(FIB_OBJS)
	$(CPPC) $(LDFLAGS) $^ -o $@

fac: $(FAC_OBJS)
	$(CPPC) $(LDFLAGS) $^ -o $@

game_test: $(GAME_OBJS)
	$(CPPC) $(LDFLAGS) $^ -o $@

homophone_puzzle: $(HOMOPHONE_OBJS)
	$(CPPC) $(LDFLAGS) $^ -o $@

$(OBJ_DIR)/anagram_finder.o: anagram_finder.cpp | $(OBJ_DIR)
	$(CPPC) $(CPPCFLAGS) $< -o $@

$(OBJ_DIR)/fib.o: fib.cpp fib.h | $(OBJ_DIR) 
	$(CPPC) $(CPPCFLAGS) $< -o $@

$(OBJ_DIR)/fib_generator.o: fib_generator.cpp fib.h | $(OBJ_DIR) 
	$(CPPC) $(CPPCFLAGS) $< -o $@

$(OBJ_DIR)/fac.o: fac.cpp fac.h | $(OBJ_DIR)
	$(CPPC) $(CPPCFLAGS) $< -o $@

$(OBJ_DIR)/game.o: game.cpp game.h | $(OBJ_DIR)
	$(CPPC) $(CPPCFLAGS) $< -o $@

$(OBJ_DIR)/game_test.o: game_test.cpp game.h | $(OBJ_DIR)
	$(CPPC) $(CPPCFLAGS) $< -o $@

$(OBJ_DIR)/homophone_puzzle.o: homophone_puzzle.cpp | $(OBJ_DIR)
	$(CPPC) $(CPPCFLAGS) $< -o $@

$(OBJ_DIR)/pronounce_dict.o: pronounce_dict.cpp pronounce_dict.h | $(OBJ_DIR)
	$(CPPC) $(CPPCFLAGS) $< -o $@

$(OBJ_DIR)/cartalk_puzzle.o: cartalk_puzzle.cpp pronounce_dict.h | $(OBJ_DIR)
	$(CPPC) $(CPPCFLAGS) $< -o $@

$(OBJ_DIR)/anagram_dict.o: anagram_dict.cpp anagram_dict.h | $(OBJ_DIR)
	$(CPPC) $(CPPCFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -rf $(OBJ_DIR) $(EXES)

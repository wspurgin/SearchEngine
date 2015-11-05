############################################################
# Makefile
############################################################

UNAME := $(shell uname)

ifeq ($(UNAME), Darwin)
        CXX = g++-4.8
else
        CXX = g++
endif

CXXFLAGS = -O2 -std=c++11

ALL = DocLoader.o DocProcessor.o StringCleaner.o AVLInterface.o IndexHandler.o QueryProcessor.o HashTableInterface.o Ranker.o UI.o
# Get current working directory
# and specify lib directory

MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
MAKE_DIR := $(dir $(MKFILE_PATH))
LIB_DIRS := $(sort $(dir $(wildcard $(MAKE_DIR)**/)))
TEST_DIR := $(MAKE_DIR)/test/
BIN_DIR := $(MAKE_DIR)../bin/

IFLAGS = $(foreach dir, $(LIB_DIRS), -I $(dir))
CXXFLAGS := $(CXXFLAGS) $(IFLAGS)

ALL := $(addprefix $(BIN_DIR), $(ALL))

$(BIN_DIR)SearchEngine.out: $(MAKE_DIR)SearchEngine.cpp $(ALL) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(MAKE_DIR)SearchEngine.cpp $(ALL)  -o $@

$(BIN_DIR)testAVL.out: $(TEST_DIR)testAVL.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_DIR)testAVL -o $@

$(BIN_DIR)testStringCleaner.out: $(TEST_DIR)testStringCleaner.cpp StringCleaner.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_DIR)testStringCleaner.cpp $(addprefix $(BIN_DIR), StringCleaner.o) -o $@

$(BIN_DIR)test_DocProcessor.out: $(TEST_DIR)test_DocProcessor.cpp $(ALL) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_DIR)test_DocProcessor.cpp $(addprefix $(BIN_DIR), $(ALL)) -o $@

$(BIN_DIR)test_AVLInterface.out: $(TEST_DIR)test_AVLInterface.cpp AVLInterface.o | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(TEST_DIR)test_AVLInterface.cpp $(addprefix $(BIN_DIR), AVLInterface.o) -o $@

# includes makefiles from submodules
include $(MAKE_DIR)**/Makefile

$(BIN_DIR):
	@echo "making dir"
	mkdir $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)

.PHONEY: print_vars, search_engine
print_vars:
	@echo "CXX => $(CXX)"
	@echo "CXXFLAGS => $(CXXFLAGS)"
	@echo "IFLAGS => $(IFLAGS)"
	@echo "MAKE_DIR => $(MAKE_DIR)"
	@echo "LIB_DIRS => $(LIB_DIRS)"
	@echo "BIN_DIR => $(BIN_DIR)"

search_engine: $(BIN_DIR)SearchEngine.out
	@echo "Finished building Search Engine"

######### END OF FILE #########


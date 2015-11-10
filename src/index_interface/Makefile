
UNAME ?= $(shell uname)

ifeq ($(UNAME), Darwin)
	CXX ?= g++-4.8
else
	CXX ?= g++
endif

IFLAGS ?= -I $(LIB_DIR)
CXXFLAGS ?= "-O2 -std=c++11 $(IFLAGS)"

MAKE_DIR ?= ./
BIN_DIR ?= ./
MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
I_CUR_DIR := $(dir $(MKFILE_PATH))
I_OBJS := $(addprefix $(BIN_DIR), HashTableInterface.o AVLInterface.o)

$(BIN_DIR)IndexHandler.o: $(I_CUR_DIR)IndexHandler.cpp $(I_OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $(I_CUR_DIR)IndexHandler.cpp  -o $@

$(BIN_DIR)HashTableInterface.o: $(I_CUR_DIR)HashTableInterface.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(BIN_DIR)AVLInterface.o: $(I_CUR_DIR)AVLInterface.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $^ -o $@



UNAME ?= $(shell uname)

ifeq ($(UNAME), Darwin)
	CXX ?= g++-4.8
else
	CXX ?= g++
endif

LIB_DIRS ?= $(sort $(dir $(wildcard ../**/)))$(abspath ../)
IFLAGS ?= $(foreach dir, $(LIB_DIRS), -I $(dir))
CXXFLAGS ?= -O2 -std=c++11 $(IFLAGS)

MAKE_DIR ?= ./
BIN_DIR ?= ./
MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST)))
DP_CUR_DIR := $(dir $(MKFILE_PATH))

$(BIN_DIR)DocLoader.o: $(DP_CUR_DIR)DocLoader.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(BIN_DIR)DocProcessor.o: $(DP_CUR_DIR)DocProcessor.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(BIN_DIR)StringCleaner.o: $(DP_CUR_DIR)StringCleaner.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $^ -o $@


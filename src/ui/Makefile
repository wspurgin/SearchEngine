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
UI_CUR_DIR := $(dir $(MKFILE_PATH))

$(BIN_DIR)UI.o: $(UI_CUR_DIR)UI.cpp | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -c $^ -o $@

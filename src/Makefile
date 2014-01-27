############################################################
# Nastasha Gerlt, Will Spurgin
# 11/18/2013
# Data Structures 2341 - Search Engine
# Makefile
############################################################

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	CXX = g++
	CXXFLAGS = -std=c++11 -O2
endif
ifeq ($(UNAME), Darwin)
	CXX = clang++
	CXXFLAGS = -stdlib=libc++ -O2
endif

ALL = DocLoader.o DocProcessor.o StringCleaner.o AVLInterface.o IndexHandler.o QueryProcessor.o HashTableInterface.o Ranker.o UI.o

all: $(ALL)

SearchEngine.out: SearchEngine.cpp $(ALL)
	$(CXX) $(CXXFLAGS) $^ -o $@

UI.o: UI.h UI.cpp
	$(CXX) $(CXXFLAGS) -c UI.cpp -o $@

QueryProcessor.o: QueryProcessor.h QueryProcessor.cpp
	$(CXX) $(CXXFLAGS) -c QueryProcessor.cpp -o $@

IndexHandler.o: IndexHandler.h IndexHandler.cpp
	$(CXX) $(CXXFLAGS) -c IndexHandler.cpp -o $@

HashTableInterface.o: HashTableInterface.h HashTableInterface.cpp
	$(CXX) $(CXXFLAGS) -c HashTableInterface.cpp -o $@

AVLInterface.o: AVLInterface.h AVLInterface.cpp AVLTree.hpp
	$(CXX) $(CXXFLAGS) -c AVLInterface.cpp -o $@

DocLoader.o: DocLoader.h DocLoader.cpp
	$(CXX) $(CXXFLAGS) -c DocLoader.cpp -o $@

DocProcessor.o: DocProcessor.h DocProcessor.cpp
	$(CXX) $(CXXFLAGS) -c DocProcessor.cpp -o $@

StringCleaner.o: StringCleaner.h StringCleaner.cpp
	$(CXX) $(CXXFLAGS) -c StringCleaner.cpp -o $@

Ranker.o: Ranker.h Ranker.cpp
	$(CXX) $(CXXFLAGS) -c Ranker.cpp -o $@	

testAVL.out: testAVL.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

testStringCleaner.out: testStringCleaner.cpp StringCleaner.o
	$(CXX) $(CXXFLAGS) $^ -o $@

test_DocProcessor.out: test_DocProcessor.cpp all
	$(CXX) $(CXXFLAGS) test_DocProcessor.cpp $(ALL) -o $@

test_AVLInterface.out: test_AVLInterface.cpp AVLInterface.o
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	\rm -rf *.out *.o
######### END OF FILE #########
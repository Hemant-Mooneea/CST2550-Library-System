#	makefile
#	Author:M00935155
#	Created:09/01/24
#	Updated:09/01/24
CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic

.PHONY: all
all: library_system

library_system: library_system.o library_functions.o
	$(CXX) $(CXXFLAGS) -o $@ $^

library_system.o: library_system.cpp library_system.h
	$(CXX) $(CXXFLAGS) -c $<

library_functions.o: library_functions.cpp library_system.h
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) *.o maths_tests
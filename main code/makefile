#	makefile
#	Author:M00935155
#	Created: 09/01/24
#	Updated: 09/01/24
CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic

.PHONY: all
all: library_system tests

library_system: library_main.o book.o librarian.o member.o person.o utilities.o
	$(CXX) $(CXXFLAGS) -o $@ $^

tests: tests.o book.o librarian.o member.o person.o utilities.o
	$(CXX) $(CXXFLAGS) -o $@ $^

library_main.o: library_main.cpp librarian.h utilities.h book.h member.h
	$(CXX) $(CXXFLAGS) -c $<

book.o: book.cpp book.h date.h member.h
	$(CXX) $(CXXFLAGS) -c $<

librarian.o: librarian.cpp librarian.h book.h member.h date.h utilities.h
	$(CXX) $(CXXFLAGS) -c $<

member.o: member.cpp member.h book.h
	$(CXX) $(CXXFLAGS) -c $<

person.o: person.cpp person.h
	$(CXX) $(CXXFLAGS) -c $<

utilities.o: utilities.cpp utilities.h date.h book.h member.h
	$(CXX) $(CXXFLAGS) -c $<

tests.o: tests.cpp book.h member.h date.h librarian.h person.h utilities.h
	$(CXX) $(CXXFLAGS) -c $<

.PHONY: clean
clean:
	$(RM) *.o library_system tests

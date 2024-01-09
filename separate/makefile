CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic

.PHONY: all
all: library_system

library_system: library_main.o book.o librarian.o member.o person.o utilities.o
	$(CXX) $(CXXFLAGS) -o $@ $^

library_main.o: library_Main.cpp librarian.h utilities.h
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

.PHONY: clean
clean:
	$(RM) *.o library_system

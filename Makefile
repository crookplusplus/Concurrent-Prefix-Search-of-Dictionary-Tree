# Authored by Chris Rook

# CXX Make variable for compiler
CXX=g++
# -std=c++11  C/C++ variant to use, e.g. C++ 2011
# -Wall       show the necessary warning files
# -g3         include information for symbolic debugger e.g. gdb 
CXXFLAGS=-std=c++11 -Wall -g3 -c

# object files
OBJS = dictionary.o populatetree.o readprefix.o countprefix.o main.o shared.o

# Program name
PROGRAM = countprefix

# The program depends upon its object files
$(PROGRAM) : $(OBJS)
	$(CXX) -pthread -o $(PROGRAM) $(OBJS)

shared.o: shared.cpp shared.h
	$(CXX) $(CXXFLAGS) shared.cpp
	
dictionary.o : dictionary.cpp dictionary.h
	$(CXX) $(CXXFLAGS) dictionary.cpp

populatetree.o : populatetree.cpp populatetree.h
	$(CXX) $(CXXFLAGS) populatetree.cpp

readprefix.o: readprefix.cpp readprefix.h
	$(CXX) $(CXXFLAGS) readprefix.cpp
    
countprefix.o: countprefix.cpp countprefix.h
	$(CXX) $(CXXFLAGS) countprefix.cpp

main.o : main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

clean :
	rm -f *.o *~ $(PROGRAM)

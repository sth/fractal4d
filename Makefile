
CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -O2

OBJECTS=gd.o algebra.o area.o generator.o main.o

generator: $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS) -lgd

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@


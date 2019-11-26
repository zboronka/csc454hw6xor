MAIN=xornet
CXX=g++
CXXFLAGS=-g -std=c++17
VPATH=src
SOURCES:=$(notdir $(wildcard src/*.cpp))
OBJECTS=$(SOURCES:%.cpp=%.o)

all: $(MAIN)

$(MAIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(MAIN) $(OBJECTS)

depend: .depend

.depend: $(SOURCES)
	rm -f ./.depend
	$(CXX) $(CXXFLAGS) -MM $^ > ./.depend;

include .depend

clean:
	rm *.o

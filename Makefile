CXX=g++
CXXFLAGS=-std=c++14 -Wall -O -g -MMD -Werror=vla
SOURCES=${wildcard ./src/*.cc ./src/buildings/*.cc ./src/nonProperties/*.cc}
OBJECTS=${SOURCES:.cc=.o}
DEPENDS=${OBJECTS:.o=.d}
EXEC=watopoly

$(EXEC): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

%.o: %.cc 
	$(CXX) -c -o $@ $< $(CXXFLAGS) 

-include ${DEPENDS}

.PHONY: clean
clean:
	rm  -f $(OBJECTS) $(DEPENDS) $(EXEC)
	
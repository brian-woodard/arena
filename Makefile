CXXFLAGS = -Wall -Wextra -pedantic-errors -g -std=c++17

all:
	g++ $(CXXFLAGS) -c Arena.cpp
	g++ $(CXXFLAGS) main.cpp -o main Arena.o

clean:
	rm -f main
	rm -f *.o

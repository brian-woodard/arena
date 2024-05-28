#CXXFLAGS = -Wall -Wextra -pedantic-errors -fsanitize=address,undefined,bounds-strict -g -std=c++17
CXXFLAGS = -Wall -Wextra -pedantic-errors -g -std=c++17

all:
	g++ $(CXXFLAGS) -c Arena.cpp
	g++ $(CXXFLAGS) -c PrintData.cpp
	g++ $(CXXFLAGS) main.cpp -o main Arena.o PrintData.o

clean:
	rm -f main
	rm -f *.o

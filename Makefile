#CXXFLAGS = -Wall -Wextra -pedantic-errors -fsanitize=address,undefined,bounds-strict -g -std=c++17
CXXFLAGS = -Wall -Wextra -pedantic-errors -g -std=c++17

all:
	g++ $(CXXFLAGS) main.cpp -o main

clean:
	rm -f main
	rm -f *.o

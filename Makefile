kilo: kilo.c
	$(CC) kilo.c -o kilo -Wall -Wextra -pedantic -std=c99

kilocpp: kilo.cpp
	$(CXX) kilo.cpp -o kilocpp -Wall -Wextra -pedantic -std=c++17


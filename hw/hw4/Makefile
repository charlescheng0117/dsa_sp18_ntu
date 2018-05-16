how_hash_table: how_hash_table.o
	g++ -o $@ $^ -std=c++11

how_hash_table.o: how_hash_table.cpp
	g++ -c how_hash_table.cpp -std=c++11

clean:
	rm *.o

all:
	g++ how.cpp -o how -std=c++11 -O2
	g++ how_hash.cpp -o hash -std=c++11 -O2

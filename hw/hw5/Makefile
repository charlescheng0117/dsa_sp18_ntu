all: fries bird

fries: fries.o
	g++ -o $@ $^ -std=c++11

fries.o: fries.cpp
	g++ -c fries.cpp -std=c++11

bird: bird.o
	g++ -o $@ $^ -std=c++11

bird.o: bird.cpp
	g++ -g -c bird.cpp -std=c++11

clean:
	rm *.o 

# all: library.cpp main.cpp
# $@ evaluates to all: The name of the file being generated.
# $< evaluates to library.cpp: The first prerequisite.
# $^ evaluates to library.cpp main.cpp: The names of all the prerequisites, with spaces between them. 

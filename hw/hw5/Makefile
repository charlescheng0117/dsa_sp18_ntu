dp: dp.o
	g++ -o $@ $^ -std=c++11

dp.o: dp.cpp
	g++ -c dp.cpp -std=c++11

clean:
	rm *.o 

# all: library.cpp main.cpp
# $@ evaluates to all: The name of the file being generated.
# $< evaluates to library.cpp: The first prerequisite.
# $^ evaluates to library.cpp main.cpp: The names of all the prerequisites, with spaces between them. 

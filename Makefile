all: Rubiks

Rubiks: main.o rubiks_cube.o  breadth_first_search.o
	g++ build/main.o build/rubiks_cube.o build/breadth_first_search.o -o bin/Rubiks

main.o: src/main.cpp
	g++ -c src/main.cpp -o build/main.o

rubiks_cube.o: src/rubiks_cube.cpp
	g++ -c src/rubiks_cube.cpp -o build/rubiks_cube.o

breadth_first_search.o: src/breadth_first_search.cpp
	g++ -c src/breadth_first_search.cpp -o build/breadth_first_search.o

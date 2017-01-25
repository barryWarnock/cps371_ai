all: Rubiks bin/Rubiks

Rubiks: main.o rubiks_cube.o 
	g++ build/main.o build/rubiks_cube.o -o bin/Rubiks

main.o: src/main.cpp
	g++ -c src/main.cpp -o build/main.o

rubiks_cube.o: src/rubiks_cube.cpp
	g++ -c src/rubiks_cube.cpp -o build/rubiks_cube.o

all: Rubiks bin/Rubiks

Rubiks: main.o search_node.o 
	g++ build/main.o build/search_node.o -o bin/Rubiks

main.o: src/main.cpp
	g++ -c src/main.cpp -o build/main.o

search_node.o: include/searchable.hpp src/search_node.cpp
	g++ -c src/search_node.cpp -o build/search_node.o

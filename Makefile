all: Rubiks

Rubiks: build/main.o build/rubiks_cube.o  build/breadth_first_search.o build/search_facade.o build/cube_ui.o build/ui.o
	g++ build/main.o build/rubiks_cube.o build/breadth_first_search.o build/search_facade.o build/cube_ui.o build/ui.o -o bin/Rubiks

build/main.o: src/main.cpp
	g++ -c src/main.cpp -o build/main.o

build/rubiks_cube.o: src/rubiks_cube.cpp include/rubiks_cube.h
	g++ -c src/rubiks_cube.cpp -o build/rubiks_cube.o

build/breadth_first_search.o: src/breadth_first_search.cpp include/breadth_first_search.h
	g++ -c src/breadth_first_search.cpp -o build/breadth_first_search.o

build/search_facade.o: src/search_facade.cpp include/search_facade.h
	g++ -c src/search_facade.cpp -o build/search_facade.o

build/ui.o: src/ui.cpp include/ui.h
	g++ -c src/ui.cpp -o build/ui.o

build/cube_ui.o: src/cube_ui.cpp include/cube_ui.h
	g++ -c src/cube_ui.cpp -o build/cube_ui.o

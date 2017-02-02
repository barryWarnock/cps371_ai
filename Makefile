FLAGS = -g

all: Rubiks

Rubiks: build/main.o build/rubiks_cube.o  build/breadth_first_search.o build/search_facade.o build/cube_ui.o build/ui.o
	g++ $(FLAGS) build/main.o build/rubiks_cube.o build/breadth_first_search.o build/search_facade.o build/cube_ui.o build/ui.o -o bin/Rubiks

build/main.o: src/main.cpp
	g++ $(FLAGS) -c src/main.cpp -o build/main.o

build/rubiks_cube.o: src/rubiks_cube.cpp include/rubiks_cube.h
	g++ -c $(FLAGS)  src/rubiks_cube.cpp -o build/rubiks_cube.o

build/breadth_first_search.o: src/breadth_first_search.cpp include/breadth_first_search.h
	g++ -c $(FLAGS) src/breadth_first_search.cpp -o build/breadth_first_search.o

build/search_facade.o: src/search_facade.cpp include/search_facade.h
	g++ -c $(FLAGS) src/search_facade.cpp -o build/search_facade.o

build/ui.o: src/ui.cpp include/ui.h
	g++ -c $(FLAGS) src/ui.cpp -o build/ui.o

build/cube_ui.o: src/cube_ui.cpp include/cube_ui.h
	g++ -c $(FLAGS) src/cube_ui.cpp -o build/cube_ui.o

tests:
	g++ $(FLAGS) test/cube_tests.cpp src/rubiks_cube.cpp -o test/run_tests

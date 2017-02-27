FLAGS = -O3
CPP = g++ -c $(FLAGS)  $< -o $@
LINK = g++ $(FLAGS) $^ -o $@

bin/ai: build/main.o build/rubiks_cube.o  build/breadth_first_search.o build/a_star_search.o build/search_facade.o build/cube_ui.o build/ui.o build/record_search_results.o build/cube_experiments.o build/sbp_impl.o build/neural_net.o
	$(LINK)

build/main.o: src/main.cpp
	$(CPP)

build/rubiks_cube.o: src/rubiks_cube.cpp include/rubiks_cube.h
	$(CPP)

build/breadth_first_search.o: src/breadth_first_search.cpp include/breadth_first_search.h
	$(CPP)

build/a_star_search.o: src/a_star_search.cpp include/a_star_search.h
	$(CPP)

build/search_facade.o: src/search_facade.cpp include/search_facade.h
	$(CPP)

build/ui.o: src/ui.cpp include/ui.h
	$(CPP)

build/cube_ui.o: src/cube_ui.cpp include/cube_ui.h
	$(CPP)

build/record_search_results.o: src/record_search_results.cpp include/record_search_results.h
	$(CPP)

build/cube_experiments.o: src/cube_experiments.cpp include/cube_experiments.h
	$(CPP)

build/sbp_impl.o: src/sbp_impl.cpp include/sbp_impl.h
	$(CPP)

build/neural_net.o: src/neural_net.cpp include/neural_net.h build/sbp_impl.o
	$(CPP)

tests: test/run_tests

test/run_tests: build/rubiks_cube.o build/a_star_search.o test/cube_tests.cpp test/neural_net_tests.cpp build/neural_net.o build/sbp_impl.o test/tests.cpp test/tests.h
	g++ $^ -o $@

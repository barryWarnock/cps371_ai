cmake_minimum_required(VERSION 3.6)
project(cpsc371_ai)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-DINTELLIJ)

set(SOURCE_FILES
        src/main.cpp
        include/searchable.h src/rubiks_cube.cpp include/rubiks_cube.h include/search.h include/breadth_first_search.h
        include/a_star_search.h include/cube_experiments.h include/cube_ui.h include/record_search_results.h
        include/search_facade.h include/ui.h
        src/breadth_first_search.cpp src/ui.cpp src/cube_ui.cpp src/search_facade.cpp src/a_star_search.cpp
        src/cube_experiments.cpp src/record_search_results.cpp include/sbp_impl.h src/sbp_impl.cpp src/neural_net.cpp
        include/neural_net.h include/neural_net_ui.h src/neural_net_ui.cpp include/stochastic_back_propogation.h
        src/stochastic_back_propogation.cpp include/serialize_cube.h src/serialize_cube.cpp include/neural_net_genome.h
        include/genetic_algorithm.h src/neural_net_genome.cpp src/genetic_algorithm.cpp include/genetic_algorithm_ui.h
        src/genetic_algorithm_ui.cpp include/net_cube_solver.h src/net_cube_solver.cpp test/genetic_algorithm_tests.cpp)

add_executable(cpsc371_ai ${SOURCE_FILES})
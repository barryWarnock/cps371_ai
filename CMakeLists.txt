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
        src/cube_experiments.cpp src/record_search_results.cpp include/sbp_impl.h src/sbp_impl.cpp src/neural_net.cpp include/neural_net.h)

add_executable(cpsc371_ai ${SOURCE_FILES})
#include <iostream>
#include "../include/rubiks_cube.h"

int main() {
    Rubiks_Cube cube = Rubiks_Cube(3);
    cube = cube.do_move(X, 2, CLOCKWISE);
    std::cout << cube.pretty_print_state();
    return 0;
}

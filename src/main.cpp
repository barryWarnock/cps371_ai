#include <iostream>
#include "../include/rubiks_cube.h"

int main() {
    Rubiks_Cube cube = Rubiks_Cube(2);
    cube = cube.do_move(Z, 0, CLOCKWISE);
    std::cout << cube.pretty_print_state();
    return 0;
}

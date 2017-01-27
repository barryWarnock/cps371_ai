#include <iostream>
#include "../include/rubiks_cube.h"
using namespace std;

int main() {
    cout << "how big of a cube: ";
    int n;
    cin >> n;
    cout << "which axis [x,y,z]: ";
    char inAxis;
    cin >> inAxis;
    Axis axis;
    switch (inAxis) {
        case 'x':
            axis = X;
            break;
        case 'y':
            axis = Y;
            break;
        case 'z':
            axis = Z;
            break;
    }
    cout << "which slice: ";
    int slice;
    cin >> slice;
    Rubiks_Cube cube = Rubiks_Cube(n);
    cube = cube.do_move(axis, slice, COUNTER_CLOCKWISE);
    cout << cube.pretty_print_state();
    return 0;
}

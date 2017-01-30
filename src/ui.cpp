#ifndef UI_H
#define UI_H

#include <iostream>

#include "../include/ui.h"
#include "../include/cube_ui.h"
using namespace std;

void ui_start() {
    cout << "which activity: \n"
         << "[0] exit\n"
         << "[1] Rubiks Cube\n" << endl;
    int input;
    cin >> input;

    switch (input) {
        case 0:
            cout << "exiting" << endl;
            return;
        case 1:
            cube_ui_main();
            ui_start();
            break;
        default:
            cout << "not a valid problem" << endl;
            ui_start();
            break;
    }
}

#endif

#include <iostream>

#include "../include/ui.h"
#include "../include/cube_ui.h"
#include "../include/neural_net_ui.h"
#include "../include/genetic_algorithm_ui.h"

using namespace std;

void ui_start() {
    int input;
    do {
        cout << "which activity: \n"
             << "[0] exit\n"
             << "[1] Rubiks Cube\n"
             << "[2] Neural Net\n"
             << "[3] Genetic Algorithm"
             << endl;
        cin >> input;

        switch (input) {
            case 0:
                cout << "exiting" << endl;
                break;
            case 1:
                cube_ui_main();
                break;
            case 2:
                neural_net_ui_main();
                break;
            case 3:
                genetic_algorithm_ui_main();
                break;
            default:
                cout << "not a valid problem" << endl;
                break;
        }
    } while (input);
}


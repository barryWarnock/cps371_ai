#include <cstdlib>
#include "../include/cube_ui.h"
#include "../include/search_facade.h"
#include "../include/record_search_results.h"
#include "../include/cube_experiments.h"
using namespace std;

shared_ptr<Rubiks_Cube> create_cube();
void manually_rotate(shared_ptr<Rubiks_Cube>* cube);
void randomly_rotate(shared_ptr<Rubiks_Cube>* cube);
void view_cube(shared_ptr<Rubiks_Cube> cube);
void solve_cube(shared_ptr<Rubiks_Cube>* cube);
void experiments();

void cube_ui_main() {
    shared_ptr<Rubiks_Cube> cube = create_cube();
    int input = 1;
    while (input != 0) {
        cout << "What would you like to do: \n"
             << "[0] exit\n"
             << "[1] manually rotate\n"
             << "[2] randomly rotate\n"
             << "[3] view cube\n"
             << "[4] solve cube\n"
             << "[5] experiments\n"
             << endl;
        cin >> input;
        switch (input) {
            case 0:
                return;
            case 1:
                manually_rotate(&cube);
                break;
            case 2:
                randomly_rotate(&cube);
                break;
            case 3:
                view_cube(cube);
                break;
            case 4:
                solve_cube(&cube);
                break;
            case 5:
                experiments();
                break;
            default:
                cout << "not a valid option" << endl;
                break;
        }
    }
}

shared_ptr<Rubiks_Cube> create_cube() {
    int n;
    cout << "how big of a cube: ";
    cin >> n;
    return shared_ptr<Rubiks_Cube>(new Rubiks_Cube(n));
}

void manually_rotate(shared_ptr<Rubiks_Cube> *cube) {
    string move;
    cout << "enter a move [XYZ][slice#][CW|CCW]: ";
    cin >> move;
    Rubiks_Cube* newCube = (*cube)->do_move(move);
    if (!newCube) {
        cout << move << " is not a valid move, a valid move looks like [XYZ][slice#][CW|CCW] eg. X0CW" << endl;
    }
    (*cube).reset(newCube);
}

void randomly_rotate(shared_ptr<Rubiks_Cube> *cube) {
    int depth;
    cout << "What depth would you like to permute the cube to: ";
    cin >> depth;

    Cube_Axis axis;
    int slice;
    Cube_Direction direction;
    for (int i = 0; i < depth; i++) {
        slice = rand() % (*cube)->size();
        direction = (Cube_Direction)(rand() % 2);
        axis = (Cube_Axis)(rand() % 3);
        (*cube).reset((*cube)->do_move(axis, slice, direction));
    }
}

void view_cube(shared_ptr<Rubiks_Cube> cube) {
    cout << cube->pretty_print_state() << endl;
}

void solve_cube(shared_ptr<Rubiks_Cube>* cube) {
    cout << "Search type: \n"
         << "[0] BFS\n"
         << "[1] A*\n"
         << endl;

    int input;
    cin >> input;

    Search_Type type;
    switch (input) {
        case 0:
            type = BFS;
            break;
        case 1:
            type = A_STAR;
            break;
        default:
            cout << "Not a valid search type" << endl;
            return;
    }

    shared_ptr<Search_Node> solved = search(type, *cube, shared_ptr<Rubiks_Cube>(new Rubiks_Cube((*cube)->size())));


    list<string> moves = get_move_list(solved.get());

    cout << "The cube can be solved with the following moves: " << endl;
    for (list<string>::iterator move = moves.begin(); move != moves.end(); move++) {
        cout << "    " << *move << endl;
    }

    *cube = dynamic_pointer_cast<Rubiks_Cube>(solved->self);

    cout << "Would you like to save the results to a file [y/n]: ";
    char save;
    cin >> save;
    if (save == 'y') {
        cout << "please enter a filename: ";
        string filename;
        cin >> filename;
        bool success = record_search_results(solved.get(), filename);
        if (!success) {
            cout << "failed to write file" << endl;
        }
    }
}

void experiments() {
    cout << "enter the name of the file to save the results in: ";
    string filename;
    cin >> filename;

    cout << "Which experiment\n"
         << "[0] exit\n"
         << "[1] experiment 1 (solve at various depths)\n"
         << endl;

    int input;
    cin >> input;
    switch (input) {
        case 0:
            break;
        case 1:
            cube_experiment_1(filename);
            break;
        default:
            cout << "Not an experiment" << endl;
            break;
    }
}
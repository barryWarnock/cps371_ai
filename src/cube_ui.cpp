#include <cstdlib>
#include "../include/cube_ui.h"
#include "../include/search_facade.h"
using namespace std;

void cube_ui_main() {
    unique_ptr<Rubiks_Cube> cube = create_cube();
    int input = 1;
    while (input != 0) {
        cout << "What would you like to do: \n"
             << "[0] exit\n"
             << "[1] manually rotate\n"
             << "[2] randomly rotate\n"
             << "[3] view cube\n"
             << "[4] solve cube\n"
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
                view_cube(&cube);
                break;
            case 4:
                solve_cube(&cube);
                break;
            default:
                cout << "not a valid option" << endl;
                break;
        }
    }
}

unique_ptr<Rubiks_Cube> create_cube() {
    int n;
    cout << "how big of a cube: ";
    cin >> n;
    return unique_ptr<Rubiks_Cube>(new Rubiks_Cube(n));
}

void manually_rotate(unique_ptr<Rubiks_Cube> *cube) {
    cout << "not implemented yet" << endl;
}

void randomly_rotate(unique_ptr<Rubiks_Cube> *cube) {
    int depth;
    cout << "What depth would you like to permute the cube to: ";
    cin >> depth;

    Cube_Axis axis;
    int slice;
    Cube_Direction direction;
    for (int i = 0; i < depth; i++) {
        slice = rand() % (*cube)->size();
        direction = (Cube_Direction)(rand() % 1);
        axis = (Cube_Axis)(rand() % 2);
        (*cube).reset((*cube)->do_move(axis, slice, direction));
    }
}

void view_cube(unique_ptr<Rubiks_Cube> *cube) {
    cout << (*cube)->pretty_print_state() << endl;
}

void solve_cube(unique_ptr<Rubiks_Cube> *cube) {
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

    Rubiks_Cube goal = Rubiks_Cube((*cube)->size());
    shared_ptr<Search_Node> solved = search(type, (*cube).get(), &goal);
    list<string> moves = get_move_list(solved.get());

    cout << "The cube can be solved with the following moves: " << endl;
    for (list<string>::iterator move = moves.begin(); move != moves.end(); move++) {
        cout << "    " << *move << endl;
    }
}
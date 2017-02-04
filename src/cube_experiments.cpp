#include "../include/cube_experiments.h"
#include "../include/record_search_results.h"
#include "../include/a_star_search.h"
#include "../include/rubiks_cube.h"
#include <string>

using namespace std;

void cube_experiment_1(string filename) {
    A_Star_Search search = A_Star_Search();
    shared_ptr<Rubiks_Cube> cube;
    for(int i = 0; i < 8; i++) {
        for (int j = 1; j <= 5; j++) {
            cube = make_shared<Rubiks_Cube>(Rubiks_Cube(3));
            Cube_Axis axis;
            int slice;
            Cube_Direction direction;
            for (int k = 0; k < j; k++) {
                slice = rand() % cube->size();
                direction = (Cube_Direction)(rand() % 2);
                axis = (Cube_Axis)(rand() % 3);
                cube.reset(cube->do_move(axis, slice, direction));
            }
            shared_ptr<Search_Node> solved = search.find_path(cube, make_shared<Rubiks_Cube>(Rubiks_Cube(3)));
            record_search_results(solved.get(), filename, true);
        }
    }
}
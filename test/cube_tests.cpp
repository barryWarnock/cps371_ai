#include "../include/rubiks_cube.h"
#include "../include/a_star_search.h"
#include <string>
#include <memory>
#include <iostream>
#include "tests.h"
using namespace std;

bool test_rotation(string move, string expected, int n) {
    unique_ptr<Rubiks_Cube> cube = unique_ptr<Rubiks_Cube>(new Rubiks_Cube(n));

    cube.reset(cube->do_move(move));

    if (!cube.get()) {
        cout << "Failed rotation " << move << " invalid move" << endl;
        return false;
    }

    if (cube->get_state() == expected) {
        cout << "Rotation: " << move << ", successful" << endl;
        return true;
    }

    cout << "Failed rotation " << move << endl << " Expected: " << expected << endl << " Actual:   " << cube->get_state() << endl;
    cout << cube->pretty_print_state() << endl << endl;
    return false;
}

bool test_rotation(vector<string> moves, string expected, int n) {
    unique_ptr<Rubiks_Cube> cube = unique_ptr<Rubiks_Cube>(new Rubiks_Cube(n));

    string moveString = "";
    for (string move : moves) {
        moveString += (move + " + ");
        cube.reset(cube->do_move(move));

        if (!cube.get()) {
            cout << "Failed rotation " << move << " invalid move" << endl;
            return false;
        }

    }

    if (cube->get_state() == expected) {
        cout << "Rotation: " << moveString << ", successful" << endl;
        return true;
    }

    cout << "Failed rotation " << moveString << endl << " Expected: " << expected << endl << " Actual:   " << cube->get_state() << endl;
    cout << cube->pretty_print_state() << endl << endl;
    return false;
}

int rotate_3x3_tests() {
    vector<pair<string, string>> tests = {
            make_pair<string, string>("X0CW",  "rwwrwwrwwoyyoyyoyybbbbbbbbbgggggggggwoowoowooyrryrryrr"),
            make_pair<string, string>("X1CW",  "wrwwrwwrwyoyyoyyoybbbbbbbbbgggggggggowoowooworyrryrryr"),
            make_pair<string, string>("X2CW",  "wwrwwrwwryyoyyoyyobbbbbbbbbgggggggggoowoowoowrryrryrry"),
            make_pair<string, string>("X0CCW", "owwowwowwryyryyryybbbbbbbbbgggggggggyooyooyoowrrwrrwrr"),
            make_pair<string, string>("X1CCW", "wowwowwowyryyryyrybbbbbbbbbgggggggggoyooyooyorwrrwrrwr"),
            make_pair<string, string>("X2CCW", "wwowwowwoyyryyryyrbbbbbbbbbgggggggggooyooyooyrrwrrwrrw"),
            make_pair<string, string>("Y0CW",  "bbbwwwwwwgggyyyyyyyyybbbbbbwwwggggggooooooooorrrrrrrrr"),
            make_pair<string, string>("Y1CW",  "wwwbbbwwwyyygggyyybbbyyybbbgggwwwgggooooooooorrrrrrrrr"),
            make_pair<string, string>("Y2CW",  "wwwwwwbbbyyyyyygggbbbbbbyyyggggggwwwooooooooorrrrrrrrr"),
            make_pair<string, string>("Y0CCW", "gggwwwwwwbbbyyyyyywwwbbbbbbyyyggggggooooooooorrrrrrrrr"),
            make_pair<string, string>("Y1CCW", "wwwgggwwwyyybbbyyybbbwwwbbbgggyyygggooooooooorrrrrrrrr"),
            make_pair<string, string>("Y2CCW", "wwwwwwgggyyyyyybbbbbbbbbwwwggggggyyyooooooooorrrrrrrrr"),
            make_pair<string, string>("Z0CW",  "wwwwwwwwwyyyyyyyyyobbobbobbrggrggrggoooooogggrrrrrrbbb"),
            make_pair<string, string>("Z1CW",  "wwwwwwwwwyyyyyyyyybobbobbobgrggrggrgooogggooorrrbbbrrr"),
            make_pair<string, string>("Z2CW",  "wwwwwwwwwyyyyyyyyybbobbobboggrggrggrgggoooooobbbrrrrrr"),
            make_pair<string, string>("Z0CCW", "wwwwwwwwwyyyyyyyyyrbbrbbrbboggoggoggoooooobbbrrrrrrggg"),
            make_pair<string, string>("Z1CCW", "wwwwwwwwwyyyyyyyyybrbbrbbrbgoggoggogooobbbooorrrgggrrr"),
            make_pair<string, string>("Z2CCW", "wwwwwwwwwyyyyyyyyybbrbbrbbrggoggoggobbboooooogggrrrrrr")
    };

    int failed = 0;
    for (pair<string, string> testParams : tests) {
        if (!test_rotation(get<0>(testParams), get<1>(testParams), 3)) {
            failed++;
        }
    }

    //test face rotations
    vector<string> rotateFace0CW =  {"X0CW", "Z2CW"};
    vector<string> rotateFace0CCW = {"X0CW", "Z2CCW"};
    vector<string> rotateFace1CW =  {"X0CW", "Z0CW"};
    vector<string> rotateFace1CCW = {"X0CW", "Z0CCW"};
    vector<string> rotateFace2CW =  {"Z0CW", "X0CW"};
    vector<string> rotateFace2CCW = {"Z0CW", "X0CCW"};
    vector<string> rotateFace3CW =  {"Z0CW", "X2CW"};
    vector<string> rotateFace3CCW = {"Z0CW", "X2CCW"};
    vector<string> rotateFace4CW =  {"X0CW", "Y2CW"};
    vector<string> rotateFace4CCW = {"X0CW", "Y2CCW"};
    vector<string> rotateFace5CW =  {"X0CW", "Y0CW"};
    vector<string> rotateFace5CCW = {"X0CW", "Y0CCW"};

    failed += (int)!test_rotation(rotateFace0CW,  "rrrwwwwwwoyyoyyoyybbwbbobboggyggrggrgggwoowoobbbyrryrr", 3);
    failed += (int)!test_rotation(rotateFace0CCW, "wwwwwwrrroyyoyyoyybbrbbrbbyggoggoggwbbbwoowoogggyrryrr", 3);
    failed += (int)!test_rotation(rotateFace1CW,  "rwwrwwrwwoooyyyyyywbbobbobbyggrggrggwoowoogggyrryrrbbb", 3);
    failed += (int)!test_rotation(rotateFace1CCW, "rwwrwwrwwyyyyyyooorbbrbbybboggoggwggwoowoobbbyrryrrggg", 3);
    failed += (int)!test_rotation(rotateFace2CW,  "bwwrwwrwwgyyoyyoyyooobbbbbbrggrggrggwoowoowggyrryrrybb", 3);
    failed += (int)!test_rotation(rotateFace2CCW, "owwowwgwwryyryybyybbbbbbooorggrggrggyooyooyggwrrwrrwbb", 3);
    failed += (int)!test_rotation(rotateFace3CW,  "wwbwwrwwryygyyoyyoobbobbobbrrrggggggoowoowggwrryrrybby", 3);
    failed += (int)!test_rotation(rotateFace3CCW, "wwowwowwgyyryyryybobbobbobbggggggrrrooyooyggyrrwrrwbbw", 3);
    failed += (int)!test_rotation(rotateFace4CW,  "rwwrwwbbboyyoyygggbbbbbbyyoggggggwwrwwwooooooyrryrryrr", 3);
    failed += (int)!test_rotation(rotateFace4CCW, "rwwrwwgggoyyoyybbbbbbbbbrwwggggggoyyoooooowwwyrryrryrr", 3);
    failed += (int)!test_rotation(rotateFace5CW,  "bbbrwwrwwgggoyyoyyyyobbbbbbwwrggggggwoowoowooyyyrrrrrr", 3);
    failed += (int)!test_rotation(rotateFace5CCW, "gggrwwrwwbbboyyoyyrwwbbbbbboyyggggggwoowoowoorrrrrryyy", 3);

    return failed;
}

int rotate_2x2_tests() {
    int failed = 0;

    //test face rotations
    //the 3x3 tests ensure everything works so all we need to do to test the 2x2 is test the face rotations for each axis
    vector<string> rotateFace0CW =  {"X0CW", "Z1CW"};
    vector<string> rotateFace2CW =  {"Z0CW", "X0CW"};
    vector<string> rotateFace4CW =  {"X0CW", "Y1CW"};

    failed += (int)!test_rotation(rotateFace0CW, "rrwwoyoybwbogygrggwobbyr", 2);
    failed += (int)!test_rotation(rotateFace2CW, "bwrwgyoyoobbrgrgwowgyryb", 2);
    failed += (int)!test_rotation(rotateFace4CW, "rwbboyggbbyoggwrwwooyryr", 2);

    return failed;
}

bool test_search(shared_ptr<Rubiks_Cube> cube, shared_ptr<Rubiks_Cube> goal, string expected) {
    A_Star_Search search = A_Star_Search();
    shared_ptr<Search_Node> solved = search.find_path(cube, goal);
    bool correct = solved->self->get_state() == expected;
    if (!correct) {
        cout << "failed to sort: " << cube->get_state() << endl;
    }
    return correct;
}

int search_3x3_depth_3() {
    shared_ptr<Rubiks_Cube> cube = make_shared<Rubiks_Cube>(Rubiks_Cube(3));
    cube.reset(cube->do_move("X1CW"));
    cube.reset(cube->do_move("X1CW"));
    cube.reset(cube->do_move("Z2CW"));
    return !test_search(cube, make_shared<Rubiks_Cube>(Rubiks_Cube(3)), "wwwwwwwwwyyyyyyyyybbbbbbbbbgggggggggooooooooorrrrrrrrr");
}

int search_2x2_depth_3() {
    shared_ptr<Rubiks_Cube> cube = make_shared<Rubiks_Cube>(Rubiks_Cube(2));
    cube.reset(cube->do_move("X1CW"));
    cube.reset(cube->do_move("X1CW"));
    cube.reset(cube->do_move("Z0CW"));
    return !test_search(cube, make_shared<Rubiks_Cube>(Rubiks_Cube(2)), "wwwwyyyybbbbggggoooorrrr");
}

int cube_tests() {
    cout << "Beginning cube tests:" << endl;

    int failed = 0;
    failed += rotate_3x3_tests();
    failed += rotate_2x2_tests();
    failed += search_3x3_depth_3();
    failed += search_2x2_depth_3();

    cout << "cube tests complete" << endl << endl;

    return failed;
}
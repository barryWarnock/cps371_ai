#include "../include/rubiks_cube.h"
#include <string>
#include <memory>
using namespace std;

bool rotate_3x3_X_0_CW() {
    string expected = "";
    string move = "";
    unique_ptr<Rubiks_Cube> cube = unique_ptr<Rubiks_Cube>(new Rubiks_Cube(3));

    cube.reset(cube->do_move(move));

    printf("%s", cube->get_state());
    exit(3);
    if (cube->get_state() == expected) {
        return true;
    }

    printf("Failed rotation X0CW\n Expected: %s\n Actual: %s",
           expected,
           cube->get_state()
    );

    return false;
}

bool rotate_3x3_X_1_CW() {
    string expected = "";
    string move = "";
    unique_ptr<Rubiks_Cube> cube = unique_ptr<Rubiks_Cube>(new Rubiks_Cube(3));

    cube.reset(cube->do_move(move));

    if (cube->get_state() == expected) {
        return true;
    }
    printf("Failed rotation X0CW\n Expected: %s\n Actual: %s",
           expected,
           cube->get_state()
    );
    return false;
}

bool rotate_3x3_X_2_CW() {
    string expected = "";
    string move = "";
    unique_ptr<Rubiks_Cube> cube = unique_ptr<Rubiks_Cube>(new Rubiks_Cube(3));

    cube.reset(cube->do_move(move));

    if (cube->get_state() == expected) {
        return true;
    }
    printf("Failed rotation X0CW\n Expected: %s\n Actual: %s",
           expected,
           cube->get_state()
    );
    return false;
}

bool rotate_3x3_X_0_CCW() {
    string expected = "";
    string move = "";
    unique_ptr<Rubiks_Cube> cube = unique_ptr<Rubiks_Cube>(new Rubiks_Cube(3));

    cube.reset(cube->do_move(move));

    if (cube->get_state() == expected) {
        return true;
    }
    printf("Failed rotation X0CW\n Expected: %s\n Actual: %s",
           expected,
           cube->get_state()
    );
    return false;
}

bool rotate_3x3_X_1_CCW() {
    string expected = "";
    string move = "";
    unique_ptr<Rubiks_Cube> cube = unique_ptr<Rubiks_Cube>(new Rubiks_Cube(3));

    cube.reset(cube->do_move(move));

    if (cube->get_state() == expected) {
        return true;
    }
    printf("Failed rotation X0CW\n Expected: %s\n Actual: %s",
           expected,
           cube->get_state()
    );
    return false;
}

bool rotate_3x3_X_2_CCW() {
    string expected = "";
    string move = "";
    unique_ptr<Rubiks_Cube> cube = unique_ptr<Rubiks_Cube>(new Rubiks_Cube(3));

    cube.reset(cube->do_move(move));

    if (cube->get_state() == expected) {
        return true;
    }
    printf("Failed rotation X0CW\n Expected: %s\n Actual: %s",
           expected,
           cube->get_state()
    );
    return false;
}

bool rotate_3x3_Y_0_CW() {
    string expected = "";
    string move = "";
    unique_ptr<Rubiks_Cube> cube = unique_ptr<Rubiks_Cube>(new Rubiks_Cube(3));

    cube.reset(cube->do_move(move));

    if (cube->get_state() == expected) {
        return true;
    }
    printf("Failed rotation X0CW\n Expected: %s\n Actual: %s",
           expected,
           cube->get_state()
    );
    return false;
}

bool rotate_3x3_Y_1_CW() {
    string expected = "";
    string move = "";
    unique_ptr<Rubiks_Cube> cube = unique_ptr<Rubiks_Cube>(new Rubiks_Cube(3));

    cube.reset(cube->do_move(move));

    if (cube->get_state() == expected) {
        return true;
    }
    printf("Failed rotation X0CW\n Expected: %s\n Actual: %s",
           expected,
           cube->get_state()
    );
    return false;
}

bool rotate_3x3_Y_2_CW() {
    string expected = "";
    string move = "";
    unique_ptr<Rubiks_Cube> cube = unique_ptr<Rubiks_Cube>(new Rubiks_Cube(3));

    cube.reset(cube->do_move(move));

    if (cube->get_state() == expected) {
        return true;
    }
    printf("Failed rotation X0CW\n Expected: %s\n Actual: %s",
           expected,
           cube->get_state()
    );
    return false;
}

bool rotate_3x3_Y_0_CCW() {
    string expected = "";
    string move = "";
    Rubiks_Cube cube = Rubiks_Cube(3);
    cube = *(cube.do_move(move));
    if (cube.get_state() == expected) {
        return true;
    }
    printf("Failed rotation X0CW\n Expected: %s\n Actual: %s",
           expected,
           cube.get_state()
    );
    return false;
}

bool rotate_3x3_Y_1_CCW() {
    string expected = "";
    string move = "";
    unique_ptr<Rubiks_Cube> cube = unique_ptr<Rubiks_Cube>(new Rubiks_Cube(3));

    cube.reset(cube->do_move(move));

    if (cube->get_state() == expected) {
        return true;
    }
    printf("Failed rotation X0CW\n Expected: %s\n Actual: %s",
           expected,
           cube->get_state()
    );
    return false;
}

bool rotate_3x3_Y_2_CCW() {
    string expected = "";
    string move = "";
    unique_ptr<Rubiks_Cube> cube = unique_ptr<Rubiks_Cube>(new Rubiks_Cube(3));

    cube.reset(cube->do_move(move));

    if (cube->get_state() == expected) {
        return true;
    }
    printf("Failed rotation X0CW\n Expected: %s\n Actual: %s",
           expected,
           cube->get_state()
    );
    return false;}

bool rotate_3x3_Z_0_CW() {
    string expected = "";
    string move = "";
    unique_ptr<Rubiks_Cube> cube = unique_ptr<Rubiks_Cube>(new Rubiks_Cube(3));

    cube.reset(cube->do_move(move));

    if (cube->get_state() == expected) {
        return true;
    }
    printf("Failed rotation X0CW\n Expected: %s\n Actual: %s",
           expected,
           cube->get_state()
    );
    return false;}

bool rotate_3x3_Z_1_CW() {
    string expected = "";
    string move = "";
    unique_ptr<Rubiks_Cube> cube = unique_ptr<Rubiks_Cube>(new Rubiks_Cube(3));

    cube.reset(cube->do_move(move));

    if (cube->get_state() == expected) {
        return true;
    }
    printf("Failed rotation X0CW\n Expected: %s\n Actual: %s",
           expected,
           cube->get_state()
    );
    return false;
}

bool rotate_3x3_Z_2_CW() {
    string expected = "";
    string move = "";
    unique_ptr<Rubiks_Cube> cube = unique_ptr<Rubiks_Cube>(new Rubiks_Cube(3));

    cube.reset(cube->do_move(move));

    if (cube->get_state() == expected) {
        return true;
    }
    printf("Failed rotation X0CW\n Expected: %s\n Actual: %s",
           expected,
           cube->get_state()
    );
    return false;
}

bool rotate_3x3_Z_0_CCW() {
    string expected = "";
    string move = "";
    unique_ptr<Rubiks_Cube> cube = unique_ptr<Rubiks_Cube>(new Rubiks_Cube(3));

    cube.reset(cube->do_move(move));

    if (cube->get_state() == expected) {
        return true;
    }
    printf("Failed rotation X0CW\n Expected: %s\n Actual: %s",
           expected,
           cube->get_state()
    );
    return false;
}

bool rotate_3x3_Z_1_CCW() {
    string expected = "";
    string move = "";
    unique_ptr<Rubiks_Cube> cube = unique_ptr<Rubiks_Cube>(new Rubiks_Cube(3));

    cube.reset(cube->do_move(move));

    if (cube->get_state() == expected) {
        return true;
    }
    printf("Failed rotation X0CW\n Expected: %s\n Actual: %s",
           expected,
           cube->get_state()
    );
    return false;
}

bool rotate_3x3_Z_2_CCW() {
    string expected = "";
    string move = "";
    unique_ptr<Rubiks_Cube> cube = unique_ptr<Rubiks_Cube>(new Rubiks_Cube(3));

    cube.reset(cube->do_move(move));

    if (cube->get_state() == expected) {
        return true;
    }
    printf("Failed rotation X0CW\n Expected: %s\n Actual: %s",
           expected,
           cube->get_state()
    );
    return false;
}

int rotate_3x3_tests() {
    vector<function<bool()>> tests = {rotate_3x3_X_0_CW,
                          rotate_3x3_X_0_CW,
                          rotate_3x3_X_0_CW,
                          rotate_3x3_Y_1_CW,
                          rotate_3x3_Y_1_CW,
                          rotate_3x3_Y_1_CW,
                          rotate_3x3_Z_2_CW,
                          rotate_3x3_Z_2_CW,
                          rotate_3x3_Z_2_CW,
                          rotate_3x3_X_0_CCW,
                          rotate_3x3_X_0_CCW,
                          rotate_3x3_X_0_CCW,
                          rotate_3x3_Y_1_CCW,
                          rotate_3x3_Y_1_CCW,
                          rotate_3x3_Y_1_CCW,
                          rotate_3x3_Z_2_CCW,
                          rotate_3x3_Z_2_CCW,
                          rotate_3x3_Z_2_CCW};

    int failed = 0;
    for (function<bool()> test : tests) {
        if (!test()) {
            failed++;
        }
    }

    return failed;
}

int main() {
    int failed = 0;
    failed += rotate_3x3_tests();
    printf((failed ? "failed %d tests" : "all tests passed"), failed);
}
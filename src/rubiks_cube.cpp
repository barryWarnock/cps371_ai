#include <stdexcept>
#include <vector>
#include <functional>
#include "../include/rubiks_cube.h"

using namespace std;

Rubiks_Cube::Rubiks_Cube(int n) {
    this->n = n;
    this->cubeString = "";

    for (int i = 0; i < n*n*6; i++) {
        int face = i / (n*n);
        switch (face) {
            case 0:
                this->cubeString += (char)WHITE;
                break;
            case 1:
                this->cubeString += (char)YELLOW;
                break;
            case 2:
                this->cubeString += (char)BLUE;
                break;
            case 3:
                this->cubeString += (char)GREEN;
                break;
            case 4:
                this->cubeString += (char)ORANGE;
                break;
            case 5:
                this->cubeString += (char)RED;
                break;
            default:
                break;
        }
    }
}

Rubiks_Cube::Rubiks_Cube(int n, std::string startState) {
    this->n = n;
    this->cubeString = startState;
}

string Rubiks_Cube::pretty_print_state() {
    string prettyString = "";

    for (int y = 0; y < n; y++) {
        for (int i = 0; i < n; i++) {
            prettyString += " ";
        }
        for (int x = 0; x < n; x++) {
            int flippedY = flip_index(y);
            prettyString += read_logical(5, x, flippedY);
        }
        prettyString += '\n';
    }

    for (int y = 0; y < n; y++) {
        for (int i = 0; i < 4; i++) {
            int face;
            switch (i) {
                case 0:
                    face = 2;
                    break;
                case 1:
                    face = 0;
                    break;
                case 2:
                    face = 3;
                    break;
                case 3:
                    face = 1;
                    break;
            }
            for (int x = 0; x < n; x++) {
                int logicalX = x;
                if (x > 1) {
                    logicalX = flip_index(x);
                }
                prettyString += read_logical(face, logicalX, y);
            }
        }
        prettyString += '\n';
    }

    for (int y = 0; y < n; y++) {
        for (int i = 0; i < n; i++) {
            prettyString += " ";
        }
        for (int x = 0; x < n; x++) {
            prettyString += read_logical(4, x, y);
        }
        prettyString += '\n';
    }

    return prettyString;
}

std::vector<Searchable> Rubiks_Cube::generate_children() {
    return vector<Searchable>();
}

string Rubiks_Cube::get_state() {
    return this->cubeString;
}

int Rubiks_Cube::run_heuristic() {
    return 0;
}

int Rubiks_Cube::index_from_fxy(int face, int x, int y) {
    return (n*n*face)+(y*n)+x;
}

Colour Rubiks_Cube::read_logical(int face, int x, int y) {
    return (Colour)this->cubeString[index_from_fxy(face,x,y)];
}

void Rubiks_Cube::write_logical(int face, int x, int y, Colour value) {
    this->cubeString[index_from_fxy(face,x,y)] = (char)value;
}

int Rubiks_Cube::flip_index(int index) {
    return n-1-index;
}

int Rubiks_Cube::translate_face(int face, Axis axis, Direction direction) {
    switch (axis) {
        case X:
            if (direction == CLOCKWISE) {
                switch (face) {
                    case 0:
                        return 4;
                    case 1:
                        return 5;
                    case 4:
                        return 1;
                    case 5 :
                        return 0;
                }
            } else {
                switch (face) {
                    case 0:
                        return 5;
                    case 1:
                        return 4;
                    case 4:
                        return 0;
                    case 5:
                        return 1;
                }
            }
            break;
        case Y:
            if (direction == CLOCKWISE) {
                switch (face) {
                    case 0:
                        return 3;
                    case 1:
                        return 2;
                    case 2:
                        return 0;
                    case 3:
                        return 1;
                }
            } else {
                switch (face) {
                    case 0:
                        return 2;
                    case 1:
                        return 3;
                    case 2:
                        return 1;
                    case 3:
                        return 0;
                }
            }
            break;
        case Z:
            if (direction == CLOCKWISE) {
                switch (face) {
                    case 2:
                        return 4;
                    case 3:
                        return 5;
                    case 4:
                        return 3;
                    case 5:
                        return 2;
                }
            } else {
                switch (face) {
                    case 2:
                        return 5;
                    case 3:
                        return 4;
                    case 4:
                        return 2;
                    case 5:
                        return 3;
                }
            }
            break;
    }
}

Rubiks_Cube Rubiks_Cube::do_move(Axis axis, int slice, Direction direction) {
    if (slice < 0 or slice > n-1) {
        throw std::out_of_range("slice");
    }

    Rubiks_Cube newCube = *this;

    vector<int> faces = {};
    std::function<int(int,int)> translate_x_same_parity;
    std::function<int(int,int)> translate_x_different_parity;
    std::function<int(int,int)> translate_y_same_parity;
    std::function<int(int,int)> translate_y_different_parity;

    auto x_identity = [](int x, int y) {return x;};
    auto x_swap = [this](int x, int y) {return flip_index(x);};
    auto y_identity = [](int x, int y) {return y;};
    auto y_swap = [this](int x, int y) {return flip_index(y);};

    switch (axis) {
        case X:
            faces = {0,1,4,5};

            translate_x_same_parity = x_identity;
            translate_x_different_parity = x_identity;
            translate_y_same_parity = y_identity;
            translate_y_different_parity = y_swap;
            break;
        case Y:
            faces = {0,1,2,3};
            translate_x_same_parity = x_identity;
            translate_x_different_parity = x_swap;
            translate_y_same_parity = y_identity;
            translate_y_different_parity = y_identity;
            break;
        case Z:
            faces = {2,3,4,5};
            translate_x_same_parity = y_swap;
            translate_x_different_parity = y_swap;
            translate_y_same_parity = x_identity;
            translate_y_different_parity = x_swap;
            break;
    }

    auto determine_slice_axis = [this](int face, Axis axis){
        if (axis == X or axis == Y) {
            return axis;
        } else {
            switch (face) {
                case 2:
                    return X;
                    break;
                case 3:
                    return X;
                    break;
                case 4:
                    return Y;
                    break;
                case 5:
                    return Y;
                    break;
            }
        }
    };

    auto slice_to_index = [this](int slice, Axis sliceAxis, Axis rotation) {
        if (rotation == X or rotation == Y) {
            return slice;
        } else {
            if (sliceAxis == X) {
                return slice;
            } else if (sliceAxis == Y) {
                return flip_index(slice);
            }
        }
    };

    for (int i = 0; i < 4; i++) {
        int face = faces[i];
        int toFace = translate_face(face, axis, direction);
        Axis sliceAxis = determine_slice_axis(face, axis);
        for (int j = 0; j < n; j++) {
            int x, y;
            if (sliceAxis == X) {
                x = slice_to_index(slice, sliceAxis, axis);
                y = j;
            } else {
                x = j;
                y = slice_to_index(slice, sliceAxis, axis);
            }
            int toX, toY;
            if (face % 2 == toFace % 2) {
                toX = translate_x_same_parity(x, y);
                toY = translate_y_same_parity(x, y);
            } else {
                toX = translate_x_different_parity(x, y);
                toY = translate_y_different_parity(x, y);
            }
            newCube.write_logical(toFace, toX, toY, this->read_logical(face, x, y));
        }
    }
    return newCube;
}

void Rubiks_Cube::rotate_face(int face, Direction direction) {
    if (face < 0 or face > 5) {
        throw std::out_of_range("face");
    }
}


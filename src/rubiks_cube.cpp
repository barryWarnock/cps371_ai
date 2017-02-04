#include <stdexcept>
#include <vector>
#include <functional>
#include <regex>
#include "../include/rubiks_cube.h"

#ifndef INTELLIJ
#define WHITE_STRING "\x1b[38;2;255;255;255m\u25A0\033[0;39m"
#define YELLOW_STRING "\x1b[38;2;255;255;0m\u25A0\033[0;39m"
#define BLUE_STRING "\x1b[38;2;0;0;255m\u25A0\033[0;39m"
#define GREEN_STRING "\x1b[38;2;0;255;0m\u25A0\033[0;39m"
#define ORANGE_STRING "\x1b[38;2;255;106;00m\u25A0\033[0;39m"
#define RED_STRING "\x1b[38;2;255;0;0m\u25A0\033[0;39m"
#endif

#ifdef INTELLIJ
#define WHITE_STRING "w"
#define YELLOW_STRING "y"
#define BLUE_STRING "b"
#define GREEN_STRING "g"
#define ORANGE_STRING "o"
#define RED_STRING "r"
#endif

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

Rubiks_Cube::Rubiks_Cube(int n, string startState) {
    this->n = n;
    this->cubeString = startState;
}

string colour_to_string(Cube_Colour colour) {
    switch (colour) {
        case WHITE:
            return WHITE_STRING;
        case YELLOW:
            return YELLOW_STRING;
        case BLUE:
            return BLUE_STRING;
        case GREEN:
            return GREEN_STRING;
        case ORANGE:
            return ORANGE_STRING;
        case RED:
            return RED_STRING;
    }
}

string Rubiks_Cube::pretty_print_state() {
    string prettyString = "";

    for (int y = 0; y < n; y++) {
        for (int i = 0; i < n; i++) {
            prettyString += " ";
        }
        for (int x = 0; x < n; x++) {
            int flippedY = flip_index(y);
            prettyString += colour_to_string(read_logical(5, x, flippedY));
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
                if (face % 2 == 1) {
                    logicalX = flip_index(x);
                }
                prettyString += colour_to_string(read_logical(face, logicalX, y));
            }
        }
        prettyString += '\n';
    }

    for (int y = 0; y < n; y++) {
        for (int i = 0; i < n; i++) {
            prettyString += " ";
        }
        for (int x = 0; x < n; x++) {
            prettyString += colour_to_string(read_logical(4, x, y));
        }
        prettyString += '\n';
    }

    return prettyString;
}

std::vector<Search_Node*> Rubiks_Cube::generate_children() {
    vector<Search_Node*> children = vector<Search_Node*>();

    for (int axis = X; axis <= Z; axis++) {
        for (int direction = CLOCKWISE; direction <= COUNTER_CLOCKWISE; direction++) {
            for (int slice = 0; slice < n; slice++) {
                Search_Node* node = new Search_Node;
                node->self = shared_ptr<Rubiks_Cube>(this->do_move((Cube_Axis)axis, slice, (Cube_Direction)direction));
                string move = "";
                switch ((Cube_Axis)axis) {
                    case X:
                        move += 'X';
                        break;
                    case Y:
                        move += 'Y';
                        break;
                    case Z:
                        move += 'Z';
                        break;
                }

                move += to_string(slice);

                switch ((Cube_Direction)direction) {
                    case CLOCKWISE:
                        move += "CW";
                        break;
                    case COUNTER_CLOCKWISE:
                        move += "CCW";
                        break;
                }

                node->move = move;
                node->heuristic_value = node->self->run_heuristic();

                children.push_back(node);
            }
        }
    }
    return children;
}

string Rubiks_Cube::get_state() {
    return this->cubeString;
}

int Rubiks_Cube::run_heuristic() {
    vector<char> correctFaceValue = {'w','y','b','g','o','r'};
    int offset = 0;

    for (int i = 0; i < cubeString.length(); i++) {
        int face = i/(n*n);
        if (cubeString[i] != correctFaceValue[face]) {
            offset++;
        }
    }

    //divide by n*n to ensure admissibility
    return offset/(n*n);
}

int Rubiks_Cube::index_from_fxy(int face, int x, int y) {
    return (n*n*face)+(y*n)+x;
}

Cube_Colour Rubiks_Cube::read_logical(int face, int x, int y) {
    return (Cube_Colour)this->cubeString[index_from_fxy(face,x,y)];
}

void Rubiks_Cube::write_logical(int face, int x, int y, Cube_Colour value) {
    this->cubeString[index_from_fxy(face,x,y)] = (char)value;
}

int Rubiks_Cube::flip_index(int index) {
    return n-1-index;
}

int Rubiks_Cube::translate_face(int face, Cube_Axis axis, Cube_Direction direction) {
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
                        return 5;
                    case 3:
                        return 4;
                    case 4:
                        return 2;
                    case 5:
                        return 3;
                }
            } else {
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
            }
            break;
    }
}

Rubiks_Cube* Rubiks_Cube::do_move(Cube_Axis axis, int slice, Cube_Direction direction) {
    if (slice < 0 or slice > n-1) {
        throw std::out_of_range("slice");
    }

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
            translate_y_different_parity = x_swap;
            translate_x_different_parity = y_swap;
            if (direction == COUNTER_CLOCKWISE) {
                translate_x_same_parity = y_identity;
                translate_y_same_parity = x_swap;
            } else {
                translate_x_same_parity = y_swap;
                translate_y_same_parity = x_identity;
            }
            break;
    }

    auto determine_slice_axis = [this](int face, Cube_Axis axis){
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

    auto slice_to_index = [this](int slice, Cube_Axis sliceAxis, Cube_Axis rotation) {
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

    Rubiks_Cube* newCube = new Rubiks_Cube(n, this->cubeString);

    for (int i = 0; i < 4; i++) {
        int face = faces[i];
        int toFace = translate_face(face, axis, direction);
        Cube_Axis sliceAxis = determine_slice_axis(face, axis);
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
            newCube->write_logical(toFace, toX, toY, this->read_logical(face, x, y));
        }
    }

    //if the slice is on the edge make sure the right face is rotated
    if (slice == 0 or slice == n-1) {
        int face;
        switch (axis) {
            case X:
                if (slice == 0) {
                    face = 2;
                } else if (slice == n-1) {
                    face = 3;
                }
                break;
            case Y:
                if (slice == 0) {
                    face = 5;
                } else if (slice == n-1) {
                    face = 4;
                }
                break;
            case Z:
                if (slice == 0) {
                    face = 1;
                } else if (slice == n-1) {
                    face = 0;
                }
                break;
        }
        newCube->rotate_face(face, direction);
    }

    return newCube;
}
Rubiks_Cube* Rubiks_Cube::do_move(string move) { //returns nullptr on an invalid move string
    regex axisRegex ("^[X-Z](?=\\d)");
    regex sliceRegex ("\\d+(?=C?CW$)");
    regex directionRegex ("C?CW$");

    smatch axisMatch;
    regex_search(move, axisMatch, axisRegex);
    smatch directionMatch;
    regex_search(move, directionMatch, directionRegex);
    smatch sliceMatch;
    regex_search(move, sliceMatch, sliceRegex);

    if (axisMatch.empty()) {
        return nullptr;
    }
    if (sliceMatch.empty()) {
        return nullptr;
    }
    if (directionMatch.empty()) {
        return nullptr;
    }

    string directionString = directionMatch.str(0);
    string axisString = axisMatch.str(0);
    string sliceString = sliceMatch.str(0);
    Cube_Axis axis;
    int slice;
    Cube_Direction direction;

    if (axisString == "X") {
        axis = X;
    } else if (axisString == "Y") {
        axis = Y;
    } else if (axisString == "Z") {
        axis = Z;
    }

    slice = stoi(sliceString);
    if (slice < 0 or slice > this->n) {
        return nullptr;
    }

    if (directionString == "CW") {
        direction = CLOCKWISE;
    } else if (directionString == "CCW") {
        direction = COUNTER_CLOCKWISE;
    }

    return do_move(axis, slice, direction);
}

//direction is the direction the slice is moving, not relative to the face itself
void Rubiks_Cube::rotate_face(int face, Cube_Direction direction) {
    if (face < 0 or face > 5) {
        throw std::out_of_range("face");
    }

    std::function<int(int)> translate_x;
    std::function<int(int)> translate_y;

    if (direction == CLOCKWISE) {
        translate_x = [this](int y){return this->flip_index(y);};
        translate_y = [this](int x){return x;};
    } else if (direction == COUNTER_CLOCKWISE) {
        translate_x = [this](int y){return y;};
        translate_y = [this](int x){return this->flip_index(x);};
    }

    Rubiks_Cube tempCube = *this;

    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            this->write_logical(face, translate_x(y), translate_y(x), tempCube.read_logical(face, x, y));
        }
    }
}

int Rubiks_Cube::size() {
    return this->n;
}

bool Rubiks_Cube::equal_to(Searchable *other) {
    Rubiks_Cube* otherCube = dynamic_cast<Rubiks_Cube*>(other);
    if (!otherCube) return false;
    else return this->cubeString == otherCube->cubeString;
}
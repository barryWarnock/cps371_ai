#include <fstream>
#include "../include/serialize_cube.h"
using namespace std;

std::string stringify_state(std::string state) {
    string formattedState = "";

    for (char c : state) {
        switch (c) {
            case 'b':
                formattedState += "1,-1,-1,-1,-1,-1,";
                break;
            case 'g':
                formattedState += "-1,1,-1,-1,-1,-1,";
                break;
            case 'o':
                formattedState += "-1,-1,1,-1,-1,-1,";
                break;
            case 'y':
                formattedState += "-1,-1,-1,1,-1,-1,";
                break;
            case 'r':
                formattedState += "-1,-1,-1,-1,1,-1,";
                break;
            case 'w':
                formattedState += "-1,-1,-1,-1,-1,1,";
                break;
        }
    }

    return formattedState;
}

std::string stringify_move(std::string move) {
    string formattedMove = "";

    char axis = move[0];
    char slice = move[1];
    string direction = "";
    for (int j = 2; j < move.size(); j++) {
        direction += move[j];
    }

    switch (axis) {
        case 'X':
            formattedMove += "1,-1,-1,";
            break;
        case 'Y':
            formattedMove += "-1,1,-1,";
            break;
        case 'Z':
            formattedMove += "-1,-1,1,";
            break;
    }

    switch (slice) {
        case '0':
            formattedMove += "1,-1,-1,";
            break;
        case '1':
            formattedMove += "-1,1,-1,";
            break;
        case '2':
            formattedMove += "-1,-1,1,";
            break;
    }

    if (direction == "CW") {
        formattedMove += "1,-1";
    } else {
        formattedMove += "-1,1";
    }

    return formattedMove;
}

bool write_cube(string filename, map<string, string> stateMoves) {
    ofstream file;
    file.open(filename, ios::out);
    if (!file.is_open()) {
        return false;
    }

    for (auto stateMove : stateMoves) {
        file << stateMove.first << "|" << stateMove.second << endl;
    }

    file.close();
    return true;
}
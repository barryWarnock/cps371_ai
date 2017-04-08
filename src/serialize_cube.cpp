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

vector<double> vectorize_state(string state) {
    vector<double> formattedState = {};
    vector<double> b = {1,-1,-1,-1,-1,-1};
    vector<double> g = {-1,1,-1,-1,-1,-1};
    vector<double> o = {-1,-1,1,-1,-1,-1};
    vector<double> y = {-1,-1,-1,1,-1,-1};
    vector<double> r = {-1,-1,-1,-1,1,-1};
    vector<double> w = {-1,-1,-1,-1,-1,1};
    for (char c : state) {
        switch (c) {
            case 'b':
                formattedState.insert(formattedState.end(), b.begin(), b.end());
                break;
            case 'g':
                formattedState.insert(formattedState.end(), g.begin(), g.end());
                break;
            case 'o':
                formattedState.insert(formattedState.end(), o.begin(), o.end());
                break;
            case 'y':
                formattedState.insert(formattedState.end(), y.begin(), y.end());
                break;
            case 'r':
                formattedState.insert(formattedState.end(), r.begin(), r.end());
                break;
            case 'w':
                formattedState.insert(formattedState.end(), w.begin(), w.end());
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

string parse_move(vector<double> moveVector) {
    string axis = "X";
    double biggestAxis = moveVector.at(0);
    if (moveVector.at(1) > biggestAxis) {
        axis = "Y";
        biggestAxis = moveVector.at(1);
    }
    if (moveVector.at(2) > biggestAxis) {
        axis = "Z";
    }

    string slice = "0";
    double biggestSlice = moveVector.at(3);
    if (moveVector.at(4) > biggestSlice) {
        slice = "1";
        biggestSlice = moveVector.at(4);
    }
    if (moveVector.at(5) > biggestSlice) {
        slice = "2";
    }

    string direction = "CW";
    double biggestDir = moveVector.at(6);
    if (moveVector.at(7) > biggestDir) {
        direction = "CCW";
    }

    return axis+slice+direction;
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
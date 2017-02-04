#include <fstream>
#include <list>
#include "../include/record_search_results.h"

using namespace std;

bool record_search_results(Search_Node* solved, string filename) {
    ofstream file;
    file.open(filename, ios::out);
    if (!file.is_open()) {
        return false;
    }

    list<string> lines = list<string>();
    string line;
    string lastMove = "";
    while(solved) {
        line = "";
        string state = solved->self->get_state();
        bool comma = false;
        for (char stateChar : state) {
            if (comma) line += ',';
            line += stateChar;
            comma = true;
        }
        line += '|';
        comma = false;
        for (char moveChar : lastMove) {
            if (comma) line += ',';
            line += moveChar;
            comma = true;
        }

        lines.push_front(line);

        lastMove = solved->move;
        solved = solved->parent.get();
    }

    for (string line : lines) {
        file << line;
        file << '\n';
    }

    file.close();
    return true;
}
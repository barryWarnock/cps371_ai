#include <iostream>
#include <memory>
#include <list>
#include "../include/rubiks_cube.h"
#include "../include/breadth_first_search.h"
using namespace std;

int main() {
    Breadth_First_Search search_alg = Breadth_First_Search();
    shared_ptr<Search_Node> path = search_alg.find_path(Rubiks_Cube(3).do_move(X, 2, CLOCKWISE)->do_move(Z, 2, CLOCKWISE), new Rubiks_Cube(3));

    list<string> pathString = list<string>();
    while (path) {
        pathString.push_front(path->move);
        pathString.push_front("\n");
        pathString.push_front(path->self->pretty_print_state());
        pathString.push_front("\n");
        path = path->parent;
    }
    for (list<string>::iterator s = pathString.begin(); s != pathString.end(); s++) {
        cout << *s;
    }
    return 0;
}

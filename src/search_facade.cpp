#include "../include/search_facade.h"
using namespace std;

shared_ptr<Search_Node> search(Search_Type type, Searchable* start, Searchable* goal) {
    unique_ptr<Search> searchAlgorithm = nullptr;
    switch (type) {
        case BFS:
            searchAlgorithm = unique_ptr<Search>(new Breadth_First_Search());
            break;
        case A_STAR:
            exit(2);//not yet implemented
            break;
    }

    return searchAlgorithm->find_path(start, goal);
}

list<string> get_move_list(Search_Node *node) {
    list<string> moveList = list<string>();
    while (node) {
        moveList.push_front(node->move);
        node = node->parent.get();
    }
    return moveList;
}
#include "../include/search_facade.h"
#include "../include/a_star_search.h"

using namespace std;

shared_ptr<Search_Node> search(Search_Type type, shared_ptr<Searchable> start, shared_ptr<Searchable> goal) {
    unique_ptr<Search> searchAlgorithm = nullptr;
    switch (type) {
        case BFS:
            searchAlgorithm = unique_ptr<Search>(new Breadth_First_Search());
            break;
        case A_STAR:
            searchAlgorithm = unique_ptr<Search>(new A_Star_Search());
            break;
    }

    return searchAlgorithm->find_path(start, goal);
}

vector<shared_ptr<Search_Node>> search(Search_Type type, vector<shared_ptr<Searchable>> starts, shared_ptr<Searchable> goal) {
    vector<shared_ptr<Search_Node>> paths = vector<shared_ptr<Search_Node>>();
    for (shared_ptr<Searchable> start : starts) {
        paths.push_back(search(type, start, goal));
    }
    return paths;
}

list<string> get_move_list(Search_Node *node) {
    list<string> moveList = list<string>();
    while (node) {
        moveList.push_front(node->move);
        node = node->parent.get();
    }
    return moveList;
}
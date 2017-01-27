#include <list>
#include <iostream>
#include "../include/breadth_first_search.h"
#include "../include/searchable.h"

using namespace std;

vector<Search_Node*> Breadth_First_Search::find_path(Searchable *start, Searchable *goal) {
    std::list<Search_Node*> openList = list<Search_Node*>();
    vector<Search_Node*> closedList = vector<Search_Node*>();

    Search_Node* startNode = new Search_Node;
    startNode->parent = nullptr;
    startNode->move = nullptr;
    startNode->self = start;
    startNode->depth = 0;

    openList.push_back(startNode);

    bool found = false;
    Search_Node* final = nullptr;

    while (!found) {

        found = true;
    }

    vector<Search_Node*> path = vector();
    Search_Node* currentNode = final;
    while (currentNode) {
        path.push_back(currentNode);
        currentNode = currentNode->parent;
    }

    //free memory or use shared pointers, it's too late to figure that out right now

    return path;
}

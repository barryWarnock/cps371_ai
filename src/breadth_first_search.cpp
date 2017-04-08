#include <list>
#include <iostream>
#include <memory>
#include <queue>
#include <algorithm>
#include <set>
#include "../include/breadth_first_search.h"

using namespace std;

shared_ptr<Search_Node> Breadth_First_Search::find_path(shared_ptr<Searchable> start, shared_ptr<Searchable> goal) {
    std::list<shared_ptr<Search_Node>> openList = list<shared_ptr<Search_Node>>();//without the std:: my ide was highlighting the line as an error
    set<string> seen = set<string>();

    Search_Node* startNode = new Search_Node;
    startNode->parent = nullptr;
    startNode->move = "";
    startNode->self = start;
    startNode->depth = 0;

    seen.insert(start->get_state());
    openList.push_back(shared_ptr<Search_Node>(startNode));

    shared_ptr<Search_Node> currentNode = nullptr;
    shared_ptr<Search_Node> finalNode = nullptr;

    while (!openList.empty()) {
        currentNode = openList.front();
        openList.pop_front();
        if (currentNode->self->equal_to(goal.get())) {
            finalNode = currentNode;
            break;
        } else {
            vector<Search_Node*> children = currentNode->self->generate_children();
            for (Search_Node* currentChild : children) {

                if (seen.count(currentChild->self->get_state())) {
                    delete currentChild;
                    continue;
                }
                currentChild->parent = currentNode;
                currentChild->depth = currentNode->depth + 1;
                seen.insert(currentChild->self->get_state());
                openList.push_back(shared_ptr<Search_Node>(currentChild));
            }
        }
    }

    return finalNode;
}

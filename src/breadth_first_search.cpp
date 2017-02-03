#include <list>
#include <iostream>
#include <memory>
#include <queue>
#include <algorithm>
#include "../include/breadth_first_search.h"
#include "../include/searchable.h"

using namespace std;

bool has_been_seen(list<shared_ptr<Search_Node>>* openList, vector<shared_ptr<Search_Node>>* closedList, Search_Node* element) {
    auto search_list_func = [element](shared_ptr<Search_Node> other){
        return element->self->equal_to(other->self.get());
    };
    for (shared_ptr<Search_Node> seen : *openList) {
        if (seen->self->equal_to(element->self.get())) {
            return true;
        }
    }
    for (shared_ptr<Search_Node> seen : *closedList) {
        if (seen->self->equal_to(element->self.get())) {
            return true;
        }
    }
    return false;
}

shared_ptr<Search_Node> Breadth_First_Search::find_path(shared_ptr<Searchable> start, shared_ptr<Searchable> goal) {
    std::list<shared_ptr<Search_Node>> openList = list<shared_ptr<Search_Node>>();//without the std:: my ide was highlighting the line as an error
    vector<shared_ptr<Search_Node>> closedList = vector<shared_ptr<Search_Node>>();

    Search_Node* startNode = new Search_Node;
    startNode->parent = nullptr;
    startNode->move = "";
    startNode->self = start;
    startNode->depth = 0;

    openList.push_back(shared_ptr<Search_Node>(startNode));

    bool found = false;
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

                if (has_been_seen(&openList, &closedList, currentChild)) {
                    delete currentChild;
                    continue;
                }
                currentChild->parent = currentNode;
                currentChild->depth = currentNode->depth + 1;
                openList.push_back(shared_ptr<Search_Node>(currentChild));
            }
            closedList.push_back(currentNode);
        }
    }

    return finalNode;
}

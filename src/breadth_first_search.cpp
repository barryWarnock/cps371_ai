#include <list>
#include <iostream>
#include <memory>
#include <queue>
#include <algorithm>
#include "../include/breadth_first_search.h"
#include "../include/searchable.h"

using namespace std;

shared_ptr<Search_Node> Breadth_First_Search::find_path(Searchable *start, Searchable *goal) {
    std::list<shared_ptr<Search_Node>> openList = list<shared_ptr<Search_Node>>();//without the std:: my ide was highlighting the line as an error
    vector<shared_ptr<Search_Node>> closedList = vector<shared_ptr<Search_Node>>();

    Search_Node* startNode = new Search_Node;
    startNode->parent = nullptr;
    startNode->move = "";
    startNode->self = shared_ptr<Searchable>(start);
    startNode->depth = 0;

    openList.push_back(shared_ptr<Search_Node>(startNode));

    bool found = false;
    shared_ptr<Search_Node> currentNode = nullptr;
    shared_ptr<Search_Node> finalNode = nullptr;

    while (!found && !openList.empty()) { //if the list is empty that means we have exhausted every possible path which means the given goal is not reachable
        currentNode = openList.front();
        openList.pop_front();
        if (currentNode->self->equal_to(goal)) {
            found = true;
            finalNode = currentNode;
        } else {
           vector<Search_Node*> children = currentNode->self->generate_children();
            for (vector<Search_Node*>::iterator currentChild = children.begin(); currentChild != children.end(); currentChild++) {
                auto search_list_func = [currentChild](shared_ptr<Search_Node> other){
                    return (*currentChild)->self->equal_to(other->self.get());};
                if (find_if(openList.begin(), openList.end(), search_list_func) == openList.end()
                    or
                    find_if(closedList.begin(), closedList.end(), search_list_func) == closedList.end()) {
                    continue;
                }
                (*currentChild)->parent = currentNode;
                (*currentChild)->depth = currentNode->depth += 1;
                openList.push_back(shared_ptr<Search_Node>(*currentChild));
            }
            closedList.push_back(currentNode);
        }
    }

    return finalNode;
}

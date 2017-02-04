#include <string>
#include <map>
#include <queue>
#include "../include/a_star_search.h"

using namespace std;

shared_ptr<Search_Node> A_Star_Search::find_path(shared_ptr<Searchable> start, shared_ptr<Searchable> goal) {
    priority_queue<shared_ptr<Search_Node>, vector<shared_ptr<Search_Node>>, function<bool(shared_ptr<Search_Node>, shared_ptr<Search_Node>)>> openList
            = priority_queue<shared_ptr<Search_Node>, vector<shared_ptr<Search_Node>>,
                    function<bool(shared_ptr<Search_Node>, shared_ptr<Search_Node>)>>(
                    [](shared_ptr<Search_Node> a, shared_ptr<Search_Node> b){
                return (b->depth + b->heuristic_value) < (a->depth + a->heuristic_value);
            });
    map<string, int> seen = map<string, int>();

    Search_Node* startNode = new Search_Node;
    startNode->parent = nullptr;
    startNode->move = "";
    startNode->self = start;
    startNode->depth = 0;

    seen.insert(make_pair(start->get_state(), 0));
    openList.push(shared_ptr<Search_Node>(startNode));

    shared_ptr<Search_Node> currentNode = nullptr;
    shared_ptr<Search_Node> finalNode = nullptr;

    while(!openList.empty()) {
        currentNode = openList.top();
        openList.pop();

        if (currentNode->self->equal_to(goal.get())) {
            finalNode = currentNode;
            break;
        } else {
            vector<Search_Node*> children = currentNode->self->generate_children();
            for (Search_Node* currentChild : children) {

                string currentState = currentChild->self->get_state();
                if (seen.count(currentState) && seen[currentState] >= currentChild->depth) {
                    delete currentChild;
                    continue;
                }
                currentChild->parent = currentNode;
                currentChild->depth = currentNode->depth + 1;
                seen.insert(make_pair(currentState, currentChild->depth));
                openList.push(shared_ptr<Search_Node>(currentChild));
            }
        }
    }

    return finalNode;
}

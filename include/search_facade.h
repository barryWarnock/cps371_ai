#ifndef SEARCH_FACADE_H
#define SEARCH_FACADE_H

#include <memory>
#include <string>
#include <list>
#include "search.h"
#include "searchable.h"
#include "breadth_first_search.h"

enum Search_Type {
    BFS,
    A_STAR
};

/**
 * preform the selected search on start until the goal is found
 * @param type the type of search to run on start
 * @param start a Searchable representing the start state
 * @param goal a Searchable representing the goal state
 * @return a SearchNode containing the goal on success, nullptr otherwise
 */
std::shared_ptr<Search_Node> search(Search_Type type, Searchable* start, Searchable* goal);

/**
 * returns a list of the moves used to get to node from whatever start state the search resulting in node used
 * @param node the node to get the moves for
 * @return a vector of moves represented as strings
 */
std::list<std::string> get_move_list(Search_Node *node);

#endif

#ifndef __SEARCHABLE__H
#define __SEARCHABLE__H

#include <string>
#include <vector>

class Search_Node;

/**
 * Searchable is an interface that A* and BFS will be able to search
 */
class Searchable {
public:
    /**
     * returns a list of Searchables representing every possible state reachable from the current state
     * @return
     */
  virtual std::vector<Search_Node*> generate_children() = 0;
  virtual std::string get_state() = 0;
  virtual int run_heuristic() = 0;
  virtual std::string pretty_print_state() {
    return "";//an optional method that will be used for debugging and general ui niceness
  }
};

/**
 * a struct that will contain the data a search will need to store in order to be able to recreate the taken path
 */
struct Search_Node {
    Searchable* self;
    Search_Node* parent;
    int depth;
    std::string move;
};

#endif

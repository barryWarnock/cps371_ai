#ifndef __SEARCHABLE__H
#define __SEARCHABLE__H

#include <string>
#include <vector>

class Searchable;
class Search_Node;

class Searchable {
public:
  //
  virtual std::vector<Search_Node> generate_children(int current_depth) = 0;
  virtual std::string get_state() = 0;
  virtual int run_heuristic() = 0;
  virtual std::string pretty_print_state() {
    return "";//an optional method that will be used for debugging and general ui niceness
  }
};

class Search_Node {
protected:
  Searchable* self;
  Search_Node* parent;
  int depth;
  std::string move;
public:
  Search_Node(Searchable* self, Search_Node* parent, int depth, std::string);
  Searchable* get_self();
  Search_Node* get_parent();
  int get_depth();
  std::string get_move();
};
#endif

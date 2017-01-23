#include "../include/searchable.hpp"
#include <string>

using namespace std;

Search_Node::Search_Node(Searchable* self, Search_Node* parent, int depth, string move) {
  this->self = self;
  this->parent = parent;
  this->depth = depth;
  this->move = move;
}

Searchable* Search_Node::get_self() {
  return self;
}

Search_Node* Search_Node::get_parent() {
  return parent;
}

int Search_Node::get_depth() {
  return depth;
}

string Search_Node::get_move() {
  return move;
}

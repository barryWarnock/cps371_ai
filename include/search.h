#ifndef SEARCH_H
#define SEARCH_H
#include "searchable.h"
#include <memory>

class Search {
public:
    //returns a partially constructed Search_Node (self and move)
    virtual std::shared_ptr<Search_Node> find_path(std::shared_ptr<Searchable> start, std::shared_ptr<Searchable> goal) = 0;
};

#endif

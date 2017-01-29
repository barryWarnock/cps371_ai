#ifndef SEARCH_H
#define SEARCH_H
#include <string>
#include "searchable.h"
#include <vector>
#include <memory>

class Search {
public:
    //returns a partially constructed Search_Node (self and move)
    virtual std::shared_ptr<Search_Node> find_path(Searchable *start, Searchable *goal) = 0;
};

#endif

#ifndef BREADTH_FIRST_SEARCH_H
#define BREADTH_FIRST_SEARCH_H

#include <vector>
#include "search.h"

class Breadth_First_Search : protected Search {
protected:
public:
    virtual std::vector<Search_Node*> find_path(Searchable* start, Searchable* goal);
};


#endif

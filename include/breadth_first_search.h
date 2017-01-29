#ifndef BREADTH_FIRST_SEARCH_H
#define BREADTH_FIRST_SEARCH_H

#include <vector>
#include <memory>
#include "search.h"

class Breadth_First_Search : protected Search {
protected:
public:
    virtual std::shared_ptr<Search_Node> find_path(Searchable *start, Searchable *goal);
};


#endif

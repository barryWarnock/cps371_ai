#ifndef BREADTH_FIRST_SEARCH_H
#define BREADTH_FIRST_SEARCH_H

#include <vector>
#include <memory>
#include "search.h"

class Breadth_First_Search : public Search {
public:
    virtual std::shared_ptr<Search_Node> find_path(std::shared_ptr<Searchable> start, std::shared_ptr<Searchable> goal);
};


#endif

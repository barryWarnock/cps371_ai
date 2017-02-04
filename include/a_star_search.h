#ifndef STAR_SEARCH_H
#define STAR_SEARCH_H

#include "search.h"
#include "searchable.h"

class A_Star_Search : public Search {
public:
    virtual std::shared_ptr<Search_Node> find_path(std::shared_ptr<Searchable> start, std::shared_ptr<Searchable> goal);
};

#endif
#pragma once

#include "filter.h"

class Pipeline {
    public:
    ~Pipeline();
    void AddFilter(Filter* filter) {
        filters_.push_back(filter);
    }
    void ApplyPipeline(BMP& bmp);
    private:
    std::vector<Filter*> filters_;
};
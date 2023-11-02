#pragma once

#include <map>
#include <functional>

#include "filter.h"

using FilterProducer = std::function<Filter*(const FilterSettings&)>;

class FilterFactory {
public:
    void AddProducer(std::string name, std::function<Filter*(const FilterSettings&)> filter_producer);
    std::function<Filter*(const FilterSettings&)> GetProducer(const std::string& name);

private:
    std::map<std::string, FilterProducer> producer_by_name_;
};

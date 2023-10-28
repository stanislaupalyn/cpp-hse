#include "filter_factory.h"

#include "filter.h"

void FilterFactory::AddProducer(std::string name, std::function<Filter*(const FilterSettings&)> filter_producer) {
    producer_by_name_.insert({name, filter_producer});
}
std::function<Filter*(const FilterSettings&)> FilterFactory::GetProducer(const std::string& name) {
    if (!producer_by_name_.contains(name)) {
        return nullptr;
    }
    return producer_by_name_[name];
}
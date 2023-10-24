#include "filter.h"
#include <map>

using FilterProducer = std::function<Filter*(const FilterSettings&)>;

class FilterFactory {
    public:
    void AddProducer(std::string name, std::function<Filter*(const FilterSettings&)> filter_producer) {
        producer_by_name_.insert({name, filter_producer});
    }
    std::function<Filter*(const FilterSettings&)> GetProducer(const std::string& name) {
        if (!producer_by_name_.contains(name)) {
            return nullptr;
        }
        return producer_by_name_[name];
    }
    private:
    std::map<std::string, FilterProducer> producer_by_name_;
};

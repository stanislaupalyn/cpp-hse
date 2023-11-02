#include "negative_filter.h"
#include <stdexcept>

void NegativeFilter::Apply(Image& image) {
    for (size_t row = 0; row < image.GetHeight(); ++row) {
        for (size_t col = 0; col < image.GetWidth(); ++col) {
            image(row, col) = {1.0 - image(row, col).b_, 1.0 - image(row, col).g_, 1.0 - image(row, col).r_};
        }
    }
}

Filter* ProduceNegativeFilter(const FilterSettings& filter_settings) {
    if (filter_settings.name_ != "neg") {
        throw std::logic_error("Trying to produce filter with another filter settings.");
    }
    if (!filter_settings.arguments_.empty()) {
        throw std::invalid_argument("Wrong number of arguments for negative filter.");
    }
    Filter* filter_ptr = new NegativeFilter();
    return filter_ptr;
}
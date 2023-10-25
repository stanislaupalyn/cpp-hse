#include "negative_filter.h"

void NegativeFilter::Apply(BMP &bmp) {
    for (size_t row = 0; row < bmp.GetHeight(); ++row) {
        for (size_t col = 0; col < bmp.GetWidth(); ++col) {
            std::array<double, 3> color = bmp(row, col).GetNormalized();
            bmp(row, col).SetFromNormalized(1 - color[0], 1 - color[1], 1 - color[2]);
        }
    }
}

Filter* ProduceNegativeFilter(const FilterSettings& filter_settings) {
    if (filter_settings.name_ != "neg") {
        throw std::logic_error("Trying to produce filter with another filter settings");
    }
    if (!filter_settings.arguments_.empty()) {
        throw std::logic_error("Wrong number of arguments for this filter");        
    }
    Filter* filter_ptr = new NegativeFilter();
    return filter_ptr;
}
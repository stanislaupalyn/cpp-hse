#include "grayscale_filter.h"

void GrayscaleFilter::Apply(Image& image) {
    for (size_t row = 0; row < image.GetHeight(); ++row) {
        for (size_t col = 0; col < image.GetWidth(); ++col) {
            double value =
                BLUE_COEF * image(row, col).b_ + GREEN_COEF * image(row, col).g_ + RED_COEF * image(row, col).r_;
            image(row, col) = {value, value, value};
        }
    }
}

Filter* ProduceGrayscaleFilter(const FilterSettings& filter_settings) {
    if (filter_settings.name_ != "gs") {
        throw std::logic_error("Trying to produce filter with another filter settings");
    }
    if (!filter_settings.arguments_.empty()) {
        throw std::logic_error("Wrong number of arguments for this filter");
    }
    Filter* filter_ptr = new GrayscaleFilter();
    return filter_ptr;
}
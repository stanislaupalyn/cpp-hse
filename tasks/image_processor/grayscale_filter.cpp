#include "grayscale_filter.h"

void GrayscaleFilter::Apply(Image &bmp) {
    // for (size_t row = 0; row < bmp.GetHeight(); ++row) {
    //     for (size_t col = 0; col < bmp.GetWidth(); ++col) {
    //         std::array<double, 3> color = bmp(row, col).GetNormalized();
    //         double value = RED_COEF * color[0] + GREEN_COEF * color[1] + BLUE_COEF * color[2];
    //         bmp(row, col).SetFromNormalized(value, value, value);
    //     }
    // }
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
#include "crop_filter.h"
#include <stdexcept>
#include "filter.h"

void CropFilter::Apply(BMP &bmp) {
    if (bmp.GetHeight() > height_) {
        int32_t extra = bmp.GetHeight() - static_cast<int32_t>(height_);
        bmp.GetHeight() = static_cast<int32_t>(height_);
        bmp.GetData().erase(bmp.GetData().begin(), bmp.GetData().begin() + extra * bmp.GetWidth());
    }

    if (bmp.GetWidth() > width_) {
        std::vector<BMP::RGB> new_data;

        for (size_t row = 0; row < bmp.GetHeight(); ++row) {
            for (size_t col = 0; col < width_; ++col) {
                new_data.push_back(bmp(row, col));
            }
        }

        bmp.GetWidth() = static_cast<int32_t>(width_);
        bmp.GetData() = new_data;
    }
}

Filter* ProduceCropFilter(const FilterSettings& filter_settings) {
    if (filter_settings.name_ != "crop") {
        throw std::logic_error("Trying to produce filter with another filter settings");
    }
    if (filter_settings.arguments_.size() != 2) {
        throw std::logic_error("Wrong number of arguments for this filter");        
    }
    Filter* filter_ptr = new CropFilter(stoi(filter_settings.arguments_[0]), stoi(filter_settings.arguments_[1]));
    return filter_ptr;
}
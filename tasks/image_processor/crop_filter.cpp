#include "crop_filter.h"

void CropFilter::Apply(Image& image) {
    if (image.GetHeight() > height_) {
        size_t extra = image.GetHeight() - height_;
        image.GetHeight() = height_;
        image.GetData().erase(image.GetData().begin(), image.GetData().begin() + static_cast<int32_t>(extra) * static_cast<int32_t>(image.GetWidth()));
    }

    if (image.GetWidth() > width_) {
        std::vector<RGBReal> new_data;

        for (size_t row = 0; row < image.GetHeight(); ++row) {
            for (size_t col = 0; col < width_; ++col) {
                new_data.push_back(image(row, col));
            }
        }

        image.GetWidth() = static_cast<int32_t>(width_);
        image.GetData() = new_data;
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
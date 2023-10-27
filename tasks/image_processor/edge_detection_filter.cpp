#include "edge_detection_filter.h"
#include "grayscale_filter.h"

#include <algorithm>
#include <string>

void EdgeDetectionFilter::Apply(Image &image) {
    GrayscaleFilter gs;
    gs.Apply(image);

    std::vector<RGBReal> new_data(image.GetData().size());

    for (size_t row = 0; row < image.GetHeight(); ++row) {
        for (size_t col = 0; col < image.GetWidth(); ++col) {
            RGBReal sum_color{0, 0, 0};

            for (int32_t i = static_cast<int32_t>(row) - 1; i <= static_cast<int32_t>(row) + 1; ++i) {
                for (int32_t j = static_cast<int32_t>(col) - 1; j <= static_cast<int32_t>(col) + 1; ++j) {
                    int32_t x = i;
                    int32_t y = j;
                    if (x < 0) {
                        ++x;
                    }
                    if (y < 0) {
                        ++y;
                    }
                    if (x >= image.GetHeight()) {
                        --x;
                    }
                    if (y >= image.GetWidth()) {
                        --y;
                    }
                    
                    assert(x >= 0 && x < image.GetHeight());
                    assert(y >= 0 && y < image.GetWidth());

                    sum_color.b_ += image(x, y).b_ * FILTER_MATRIX[i - row + 1][j - col + 1];
                    sum_color.g_ += image(x, y).g_ * FILTER_MATRIX[i - row + 1][j - col + 1];
                    sum_color.r_ += image(x, y).r_ * FILTER_MATRIX[i - row + 1][j - col + 1];
                }   
            }
            sum_color.b_ = std::max(sum_color.b_, 0.0);
            sum_color.b_ = std::min(sum_color.b_, 1.0);
            sum_color.g_ = std::max(sum_color.g_, 0.0);
            sum_color.g_ = std::min(sum_color.g_, 1.0);
            sum_color.r_ = std::max(sum_color.r_, 0.0);
            sum_color.r_ = std::min(sum_color.r_, 1.0);

            if (sum_color.b_ >= threshold_) {
                sum_color.b_ = 1.0;
            } else {
                sum_color.b_ = 0.0;
            }
            if (sum_color.g_ >= threshold_) {
                sum_color.g_ = 1.0;
            } else {
                sum_color.g_ = 0.0;
            }
            if (sum_color.r_ >= threshold_) {
                sum_color.r_ = 1.0;
            } else {
                sum_color.r_ = 0.0;
            }

            new_data[row * image.GetWidth() + col] = sum_color;
        }
    }

    image.GetData() = new_data;
}

Filter* ProduceEdgeDetectionFilter(const FilterSettings& filter_settings) {
    if (filter_settings.name_ != "edge") {
        throw std::logic_error("Trying to produce filter with another filter settings");
    }
    if (filter_settings.arguments_.size() != 1) {
        throw std::logic_error("Wrong number of arguments for this filter");        
    }
    Filter* filter_ptr = new EdgeDetectionFilter(std::stod(filter_settings.arguments_[0]));
    return filter_ptr;
}
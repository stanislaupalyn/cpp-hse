#include "edge_detection_filter.h"
#include "grayscale_filter.h"

#include <algorithm>
#include <string>

void EdgeDetectionFilter::Apply(BMP &bmp) {
    GrayscaleFilter gs;
    gs.Apply(bmp);

    std::vector<RGB> new_data = bmp.GetData();

    for (size_t row = 0; row < bmp.GetHeight(); ++row) {
        for (size_t col = 0; col < bmp.GetWidth(); ++col) {
            std::array<double, 3> sum_color{0.0, 0.0, 0.0};

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
                    if (x >= bmp.GetHeight()) {
                        --x;
                    }
                    if (y >= bmp.GetWidth()) {
                        --y;
                    }
                    
                    assert(x >= 0 && x < bmp.GetHeight());
                    assert(y >= 0 && y < bmp.GetWidth());

                    std::array<double, 3> color = bmp(x, y).GetNormalized();
                    for (size_t cur_color = 0; cur_color < 3; ++cur_color) {
                        assert(0 <= i - row + 1 && i - row + 1 <= 2);
                        assert(0 <= j - col + 1 && j - col + 1 <= 2);
                        sum_color[cur_color] += color[cur_color] * FILTER_MATRIX[i - row + 1][j - col + 1];
                    }
                }   
            }

            for (size_t cur_color = 0; cur_color < 3; ++cur_color) {
                sum_color[cur_color] = std::max(sum_color[cur_color], 0.0);
                sum_color[cur_color] = std::min(sum_color[cur_color], 1.0);
            }

            std::array<double, 3> new_color{0.0, 0.0, 0.0};
            for (size_t cur_color = 0; cur_color < 3; ++cur_color) {
                if (sum_color[cur_color] >= threshold_) {
                    new_color[cur_color] = 1.0;
                }
            }
            new_data[row * bmp.GetWidth() + col].SetFromNormalized(new_color[0], new_color[1], new_color[2]);
        }
    }
    bmp.GetData() = new_data;
    
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
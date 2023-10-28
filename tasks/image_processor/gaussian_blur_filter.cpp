#include "gaussian_blur_filter.h"

#include "filter.h"

GaussianBlurFilter::GaussianBlurFilter(double sigma) {
    size_t size = static_cast<size_t>(ceil(SIGMA_SIZE_CONST * sigma));
    if (size % 2 == 0) {
        ++size;
    }
    filter_vector.resize(size);

    int32_t shift = static_cast<int32_t>(filter_vector.size()) / 2;

    double sum = 0;
    for (int32_t x = -shift; x <= shift; ++x) {
        double dist = x * x;
        double power = dist / (2.0 * sigma * sigma);                                      // NOLINT
        filter_vector[x + shift] = 1.0 / sqrt(2.0 * M_PI * sigma * sigma) * exp(-power);  // NOLINT
        sum += filter_vector[x + shift];
    }
    for (int32_t x = 0; x < filter_vector.size(); ++x) {
        filter_vector[x] /= sum;
    }
}

void GaussianBlurFilter::Apply(Image& image) {
    std::vector<RGBReal> new_data(image.GetData().size());

    // Apply horizontal
    {
        int32_t shift = static_cast<int32_t>(filter_vector.size()) / 2;

        for (size_t row = 0; row < image.GetHeight(); ++row) {
            for (size_t col = 0; col < image.GetWidth(); ++col) {
                RGBReal sum_color{0, 0, 0};

                for (int32_t i = static_cast<int32_t>(row); i <= static_cast<int32_t>(row); ++i) {
                    for (int32_t j = static_cast<int32_t>(col) - shift; j <= static_cast<int32_t>(col) + shift; ++j) {
                        int32_t x = i;
                        int32_t y = j;
                        while (x < 0) {
                            ++x;
                        }
                        while (y < 0) {
                            ++y;
                        }
                        while (x >= image.GetHeight()) {
                            --x;
                        }
                        while (y >= image.GetWidth()) {
                            --y;
                        }

                        double coef = filter_vector[j - col + shift];
                        sum_color.b_ += image(x, y).b_ * coef;
                        sum_color.g_ += image(x, y).g_ * coef;
                        sum_color.r_ += image(x, y).r_ * coef;
                    }
                }

                sum_color.b_ = std::max(sum_color.b_, 0.0);
                sum_color.b_ = std::min(sum_color.b_, 1.0);
                sum_color.g_ = std::max(sum_color.g_, 0.0);
                sum_color.g_ = std::min(sum_color.g_, 1.0);
                sum_color.r_ = std::max(sum_color.r_, 0.0);
                sum_color.r_ = std::min(sum_color.r_, 1.0);

                new_data[row * image.GetWidth() + col] = sum_color;
            }
        }
        image.GetData() = new_data;
    }
    // Apply vertical
    {
        int32_t shift = static_cast<int32_t>(filter_vector.size()) / 2;

        for (size_t row = 0; row < image.GetHeight(); ++row) {
            for (size_t col = 0; col < image.GetWidth(); ++col) {
                RGBReal sum_color{0, 0, 0};

                for (int32_t i = static_cast<int32_t>(row) - shift; i <= static_cast<int32_t>(row) + shift; ++i) {
                    for (int32_t j = static_cast<int32_t>(col); j <= static_cast<int32_t>(col); ++j) {
                        int32_t x = i;
                        int32_t y = j;
                        while (x < 0) {
                            ++x;
                        }
                        while (y < 0) {
                            ++y;
                        }
                        while (x >= image.GetHeight()) {
                            --x;
                        }
                        while (y >= image.GetWidth()) {
                            --y;
                        }

                        assert(x >= 0 && x < image.GetHeight());
                        assert(y >= 0 && y < image.GetWidth());

                        double coef = filter_vector[i - row + shift];
                        sum_color.b_ += image(x, y).b_ * coef;
                        sum_color.g_ += image(x, y).g_ * coef;
                        sum_color.r_ += image(x, y).r_ * coef;
                    }
                }

                sum_color.b_ = std::max(sum_color.b_, 0.0);
                sum_color.b_ = std::min(sum_color.b_, 1.0);
                sum_color.g_ = std::max(sum_color.g_, 0.0);
                sum_color.g_ = std::min(sum_color.g_, 1.0);
                sum_color.r_ = std::max(sum_color.r_, 0.0);
                sum_color.r_ = std::min(sum_color.r_, 1.0);

                new_data[row * image.GetWidth() + col] = sum_color;
            }
        }
        image.GetData() = new_data;
    }
}

Filter* ProduceGaussianBlurFilter(const FilterSettings& filter_settings) {
    if (filter_settings.name_ != "blur") {
        throw std::logic_error("Trying to produce filter with another filter settings");
    }
    if (filter_settings.arguments_.size() != 1) {
        throw std::logic_error("Wrong number of arguments for this filter");
    }
    Filter* filter_ptr = new GaussianBlurFilter(stod(filter_settings.arguments_[0]));
    return filter_ptr;
}
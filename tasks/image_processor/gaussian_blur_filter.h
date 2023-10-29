#pragma once

#include <stdexcept>

#include "filter.h"

class GaussianBlurFilter : public Filter {
public:
    explicit GaussianBlurFilter(double sigma);
    void Apply(Image& image) override;
    static constexpr double MAX_SIGMA_VALUE = 100.0;  // NOLINT
    
protected:
    static constexpr double SIGMA_SIZE_CONST = 6.0;   // NOLINT
    std::vector<double> filter_vector;
};

Filter* ProduceGaussianBlurFilter(const FilterSettings& filter_settings);
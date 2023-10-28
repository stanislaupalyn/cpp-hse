#pragma once

#include <algorithm>
#include <stdexcept>

#include "filter.h"

class SharpeningFilter : public Filter {
public:
    SharpeningFilter() {
    }
    void Apply(Image& image) override;

protected:
    static constexpr double FILTER_MATRIX[3][3] = {// NOLINT
                                                   {0.0, -1.0, 0.0},
                                                   {-1.0, 5.0, -1.0},
                                                   {0.0, -1.0, 0.0}};
};

Filter* ProduceSharpeningFilter(const FilterSettings& filter_settings);
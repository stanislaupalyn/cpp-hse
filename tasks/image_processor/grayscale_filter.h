#pragma once

#include "filter.h"

class GrayscaleFilter : public Filter {
public:
    GrayscaleFilter() {
    }
    void Apply(BMP& bmp) override;

protected:
    static constexpr double RED_COEF = 0.299;    // NOLINT
    static constexpr double GREEN_COEF = 0.587;  // NOLINT
    static constexpr double BLUE_COEF = 0.114;   // NOLINT
};

Filter* ProduceGrayscaleFilter(const FilterSettings& filter_settings);
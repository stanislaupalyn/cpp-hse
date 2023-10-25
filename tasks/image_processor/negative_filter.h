#pragma once

#include "filter.h"

class NegativeFilter : public Filter {
public:
    NegativeFilter() {
    }
    void Apply(BMP& bmp) override;

protected:
};

Filter* ProduceNegativeFilter(const FilterSettings& filter_settings);
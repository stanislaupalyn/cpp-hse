#pragma once

#include "filter.h"

class CropFilter : public Filter {
    public:
    CropFilter(size_t width, size_t height) : width_(width), height_(height) { }
    void Apply(BMP &bmp) override;

    protected:
    size_t width_;
    size_t height_;
};

Filter* ProduceCropFilter(const FilterSettings& filter_settings);
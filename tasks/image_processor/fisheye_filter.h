#pragma once

#include <stdexcept>

#include "filter.h"

// -fisheye alpha center_x center_y
// Applies to the image the distortion of the fisheye lens centered in coordinates (center_x, center_y).
// Alpha is an argument that affects the distortion of the image (bigger -- more distorted)
// Typical values are around 0.001

class FisheyeFilter : public Filter {
public:
    explicit FisheyeFilter(double alpha, double center_x, double center_y)
        : alpha_{alpha}, center_x_{center_x}, center_y_{center_y} {
    }
    void Apply(Image& image) override;

protected:
    double alpha_;
    double center_x_, center_y_;

    double x_scale_, x_shift_;
    double y_scale_, y_shift_;

    RGBReal GetPixel(double x, double y, const Image& image) const;
    double CalcShift(double x1, double x2, double cx) const;
    double GetRadialX(double x, double y) const;
    double GetRadialY(double x, double y) const;
};

Filter* ProduceFisheyeFilter(const FilterSettings& filter_settings);
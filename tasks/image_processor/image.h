#pragma once

#include <vector>

#include "rgb_color.h"

/// Class that represents an image stored in a bitmap.
/// Each pixel color is specified in data_ vector of RGBReal
/// Method for accessing color of certain pixel is implemented by
/// using parentheses perator of two arguments, coordinates of the pixel

class Image {
public:
    Image() : height_{0}, width_{0}, data_{0} {
    }

    const size_t GetHeight() const {
        return height_;
    }
    size_t& GetHeight() {
        return height_;
    }
    const size_t GetWidth() const {
        return width_;
    }
    size_t& GetWidth() {
        return width_;
    }

    std::vector<RGBReal>& GetData() {
        return data_;
    }
    const std::vector<RGBReal>& GetData() const {
        return data_;
    }

    RGBReal& operator()(size_t i, size_t j) {
        return data_[GetWidth() * i + j];
    }
    const RGBReal& operator()(size_t i, size_t j) const {
        return data_[GetWidth() * i + j];
    }

protected:
    size_t height_;
    size_t width_;
    std::vector<RGBReal> data_;
};
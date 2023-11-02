#pragma once

#include <cmath>
#include <cstdint>

class RGBReal;
class RGB24;

class RGBReal {
public:
    static constexpr double MAX_COLOR_VALUE = 255.0;  // NOLINT

    double b_;
    double g_;
    double r_;

    explicit operator RGB24() const;

private:
};

class RGB24 {
public:
    uint8_t b_;
    uint8_t g_;
    uint8_t r_;

    explicit operator RGBReal() const;
} __attribute__((packed));
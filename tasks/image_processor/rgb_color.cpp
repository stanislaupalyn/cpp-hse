#include "rgb_color.h"

#include <iostream>

RGBReal::operator RGB24() const {
    return RGB24{static_cast<uint8_t>(std::round(RGBReal::MAX_COLOR_VALUE * b_)),
                 static_cast<uint8_t>(std::round(RGBReal::MAX_COLOR_VALUE * g_)),
                 static_cast<uint8_t>(std::round(RGBReal::MAX_COLOR_VALUE * r_))};
}

RGB24::operator RGBReal() const {
    return RGBReal{static_cast<double>(b_) / RGBReal::MAX_COLOR_VALUE,
                   static_cast<double>(g_) / RGBReal::MAX_COLOR_VALUE,
                   static_cast<double>(r_) / RGBReal::MAX_COLOR_VALUE};
}
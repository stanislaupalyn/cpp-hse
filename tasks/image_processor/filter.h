#pragma once

#include "bmp.h"
#include <string>

struct FilterSettings {
    std::string name_;
    std::vector<std::string> arguments_;
};

class Filter {
    public:
    virtual ~Filter() = default;
    virtual void Apply(BMP& bmp) = 0;
};
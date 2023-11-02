#pragma once

#include <string>

#include "image.h"

struct FilterSettings {
    std::string name_;
    std::vector<std::string> arguments_;
};

class Filter {
public:
    virtual ~Filter() = default;
    virtual void Apply(Image& bmp) = 0;
};
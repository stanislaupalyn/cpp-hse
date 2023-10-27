#include "image.h"

void Image::Swap(Image& other) {
    std::swap(height_, other.height_);
    std::swap(width_, other.width_);
    std::swap(data_, other.data_);
}

Image& Image::operator=(const Image& rhs) {
    if (this == &rhs) {
        return *this;
    }
    Image tmp{rhs};
    Swap(tmp);
    return *this;
}

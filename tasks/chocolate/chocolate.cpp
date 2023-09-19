#include "chocolate.h"

#include <cstdint>

bool CanBreakSlices(int32_t height, int32_t width, int32_t slices_amount) {
    // check vertical slices
    if (slices_amount % width == 0 && slices_amount / width < height) {
        return true;
    }
    // check horizontal slices
    if (slices_amount % height == 0 && slices_amount / height < width) {
        return true;
    }
    return false;
}
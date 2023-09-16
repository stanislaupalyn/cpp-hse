#include "chocolate.h"

bool CanBreakSlices(int height, int width, int slices_amount) {
    // check vertical slices
    for (int length = 1; length < height; ++length) {
        if (length * width == slices_amount) {
            return true;
        }
    }
    // check horizontal slices
    for (int length = 1; length < width; ++length) {
        if (length * height == slices_amount) {
            return true;
        }
    }
    return false;
}
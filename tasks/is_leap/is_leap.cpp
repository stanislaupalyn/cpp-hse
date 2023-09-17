#include "is_leap.h"

#include <cstdint>

constexpr int32_t OneHundred = 100;
constexpr int32_t FourHundred = 400;

bool IsLeap(int32_t year) {
    return (year % 4 == 0 && year % OneHundred != 0) || year % FourHundred == 0;
}

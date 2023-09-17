#include "is_leap.h"

#include <cstdint>

// NO LINT
constexpr int32_t ONE_HUNDRED = 100;
// NO LINT
constexpr int32_t FOUR_HUNDRED = 400;

bool IsLeap(int32_t year) {
    return (year % 4 == 0 && year % ONE_HUNDRED != 0) || year % FOUR_HUNDRED == 0;
}
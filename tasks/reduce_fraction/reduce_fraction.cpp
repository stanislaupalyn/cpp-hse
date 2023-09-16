#include "reduce_fraction.h"

#include <numeric>

int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    int64_t common_divisor = std::gcd(numerator, denominator);
    int64_t new_numerator = numerator / common_divisor;
    int64_t new_denominator = denominator / common_divisor;
    return new_numerator + new_denominator;
}

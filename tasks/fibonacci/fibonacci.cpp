#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    int64_t previous = 0;
    int64_t current = 1;
    for (int32_t i = 0; i < n; ++i) {
        int64_t next = previous + current;
        previous = current;
        current = next;
    }
    return a;
}

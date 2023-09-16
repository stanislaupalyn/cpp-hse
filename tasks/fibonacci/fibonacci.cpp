#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    int64_t a = 0;
    int64_t b = 1;
    for (int i = 0; i < n; i++) {
        int64_t t = a + b;
        a = b;
        b = t;
    }
    return a;
}

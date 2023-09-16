#include "is_leap.h"

const int ONE_HUNDRED = 100;
const int FOUR_HUNDRED = 400;

bool IsLeap(int year) {
    return (year % 4 == 0 && year % ONE_HUNDRED != 0) || year % FOUR_HUNDRED == 0;
}

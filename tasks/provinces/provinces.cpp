#include "provinces.h"

#include <queue>

int64_t CountPassports(const std::vector<int32_t>& provinces) {
    std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>> sorted_provinces;
    for (const int32_t& province_size : provinces) {
        sorted_provinces.push(static_cast<int64_t>(province_size));
    }

    int64_t total = 0;
    while (sorted_provinces.size() > 1) {
        int64_t first_min = sorted_provinces.top();
        sorted_provinces.pop();
        int64_t second_min = sorted_provinces.top();
        sorted_provinces.pop();
        total += first_min + second_min;
        sorted_provinces.push(first_min + second_min);
    }

    return total;
}
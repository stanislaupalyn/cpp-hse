#include "provinces.h"

#include <queue>

int64_t CountPassports(const std::vector<int32_t>& provinces) {
    std::priority_queue<int32_t, std::vector<int32_t>, std::greater<int32_t>> sorted_provinces;
    for (const int32_t& province_size : provinces) {
        sorted_provinces.push(province_size);
    }

    int64_t total = 0;
    while (sorted_provinces.size() > 1) {
        int32_t first_min = sorted_provinces.top();
        sorted_provinces.pop();
        int32_t second_min = sorted_provinces.top();
        sorted_provinces.pop();
        total += first_min + second_min;
        sorted_provinces.push(first_min + second_min);
    }

    return total;
}
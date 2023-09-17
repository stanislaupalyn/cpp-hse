#include "palindrome.h"

#include <cstdint>

bool IsPalindrome(const std::string& str) {
    if (str.empty()) {
        return true;
    }
    int32_t right_index = static_cast<int32_t>(str.size()) - 1;
    for (int32_t left_index = 0; left_index < right_index; ++left_index) {
        if (str[left_index] == ' ') {
            continue;
        }
        while (right_index > left_index && str[right_index] == ' ') {
            --right_index;
        }
        if (str[left_index] != str[right_index]) {
            return false;
        }
        --right_index;
    }
    return true;
}
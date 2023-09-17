#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    if (str.empty()) {
        return true;
    }
    size_t right_index = str.size() - 1;
    for (size_t left_index = 0; left_index < right_index; ++left_index) {
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
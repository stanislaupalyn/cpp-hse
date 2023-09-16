#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    int right_pointer = static_cast<int>(str.size()) - 1;
    for (int left_pointer = 0; left_pointer < right_pointer; ++left_pointer) {
        if (str[left_pointer] == ' ') {
            continue;
        }
        while (right_pointer > left_pointer && str[right_pointer] == ' ') {
            --right_pointer;
        }
        if (str[left_pointer] != str[right_pointer]) {
            return false;
        }
        --right_pointer;
    }
    return true;
}


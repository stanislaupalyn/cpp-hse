#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    size_t leftPointer = 0;
    size_t rightPointer = str.size() - 1;
    while (leftPointer < rightPointer) {
        if (str[leftPointer] == ' ') {
            ++leftPointer;
            continue;
        }
        if (str[rightPointer] == ' ') {
            --rightPointer;
            continue;
        }
        if (str[leftPointer] != str[rightPointer]) {
            return false;
        }
        ++leftPointer;
        --rightPointer;
    }
    return true;
}

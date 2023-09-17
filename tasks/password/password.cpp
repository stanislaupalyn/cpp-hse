#include "password.h"

#include <cctype>
#include <cstdint>

constexpr char MinCode = 33;
constexpr char MaxCode = 126;
constexpr size_t MinLength = 8;
constexpr size_t MaxLength = 14;

bool ValidatePassword(const std::string& password) {
    if (password.size() < MinLength || password.size() > MaxLength) {
        return false;
    }

    for (size_t i = 0; i < password.size(); ++i) {
        if (password[i] < MinCode || password[i] > MaxCode) {
            return false;
        }
    }

    bool has_lower = false;
    bool has_upper = false;
    bool has_digit = false;
    bool has_other = false;
    for (size_t i = 0; i < password.size(); ++i) {
        if (isupper(password[i])) {
            has_upper = true;
        } else if (islower(password[i])) {
            has_lower = true;
        } else if (isdigit(password[i])) {
            has_digit = true;
        } else {
            has_other = true;
        }
    }

    if (has_lower + has_upper + has_digit + has_other < 3) {
        return false;
    }

    return true;
}

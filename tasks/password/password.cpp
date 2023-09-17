#include "password.h"

#include <cctype>
#include <cstdint>

constexpr char MIN_CODE = 33;   // NOLINT
constexpr char MAX_CODE = 126;   // NOLINT
constexpr size_t MIN_LENGTH = 8;  // NOLINT
constexpr size_t MAX_LENGTH = 14;  // NOLINT

bool ValidatePassword(const std::string& password) {
    if (password.size() < MIN_LENGTH || password.size() > MAX_LENGTH) {
        return false;
    }

    for (size_t i = 0; i < password.size(); ++i) {
        if (password[i] < MIN_CODE || password[i] > MAX_CODE) {
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

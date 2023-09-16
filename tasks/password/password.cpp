#include "password.h"

#include <cctype>

const int MIN_CODE = 33;
const int MAX_CODE = 126;
const int MIN_LENGTH = 8;
const int MAX_LENGTH = 14;

bool ValidatePassword(const std::string& password) {
    for (size_t i = 0; i < password.size(); ++i) {
        int code = static_cast<int>(password[i]);

        if (code < MIN_CODE || code > MAX_CODE) {
            return false;
        }
    }

    if (password.size() < MIN_LENGTH || password.size() > MAX_LENGTH) {
        return false;
    }

    bool has_lower = false;
    bool has_upper = false;
    bool has_digit = false;
    bool has_other = false;
    for (size_t i = 0; i < password.size(); ++i) {
        has_upper |= isupper(password[i]);
        has_lower |= islower(password[i]);
        has_digit |= isdigit(password[i]);
        has_other |= !isalpha(password[i]) && !isdigit(password[i]);
    }

    int counter = 0;
    if (has_lower) {
        counter++;
    }
    if (has_upper) {
        counter++;
    }
    if (has_digit) {
        counter++;
    }
    if (has_other) {
        counter++;
    }

    if (counter < 3) {
        return false;
    }

    return true;
}

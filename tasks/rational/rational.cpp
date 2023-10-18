#include "rational.h"

#include <sys/errno.h>
#include <numeric>
#include <streambuf>
#include <sstream>
#include <tuple>

Rational::Rational() : Rational(0) {
}

Rational::Rational(int value) : numer_{value}, denom_{1} {
}

Rational::Rational(int numer, int denom) : Rational() {
    Set(numer, denom);
}

int Rational::GetNumerator() const {
    return numer_;
}

int Rational::GetDenominator() const {
    return denom_;
}

void Rational::SetNumerator(int value) {
    numer_ = value;
    int greatest_common_divisor = std::gcd(GetNumerator(), GetDenominator());
    numer_ /= greatest_common_divisor;
    denom_ /= greatest_common_divisor;
    if (denom_ < 0) {
        numer_ *= -1;
        denom_ *= -1;
    }
    if (numer_ == 0) {
        denom_ = 1;
    }
}

void Rational::SetDenominator(int value) {
    if (value == 0) {
        throw RationalDivisionByZero{};
    }
    denom_ = value;
    int greatest_common_divisor = std::gcd(GetNumerator(), GetDenominator());
    numer_ /= greatest_common_divisor;
    denom_ /= greatest_common_divisor;
    if (denom_ < 0) {
        numer_ *= -1;
        denom_ *= -1;
    }
    if (numer_ == 0) {
        denom_ = 1;
    }
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    lhs.Set(static_cast<int64_t>(lhs.GetNumerator()) * static_cast<int64_t>(rhs.GetDenominator()) +
                static_cast<int64_t>(rhs.GetNumerator()) * static_cast<int64_t>(lhs.GetDenominator()),
            static_cast<int64_t>(lhs.GetDenominator()) * static_cast<int64_t>(rhs.GetDenominator()));
    return lhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    lhs.Set(static_cast<int64_t>(lhs.GetNumerator()) * static_cast<int64_t>(rhs.GetNumerator()),
            static_cast<int64_t>(lhs.GetDenominator()) * static_cast<int64_t>(rhs.GetDenominator()));
    return lhs;
}

Rational& operator++(Rational& ratio) {
    ratio.SetNumerator(ratio.GetNumerator() + ratio.GetDenominator());
    return ratio;
}

Rational& operator--(Rational& ratio) {
    ratio.SetNumerator(ratio.GetNumerator() - ratio.GetDenominator());
    return ratio;
}

std::istream& operator>>(std::istream& is, Rational& ratio) {
    std::string token;
    is >> token;

    std::stringstream stream;
    stream << token;
    int numer = 0;
    int denom = 1;
    stream >> numer;
    if (!stream.eof()) {
        char c = 0;
        stream >> c;
        stream >> denom;
    }
    ratio.Set(numer, denom);

    return is;
}

void Rational::Set(int64_t numer, int64_t denom) {
    if (denom == 0) {
        throw RationalDivisionByZero{};
    }
    int64_t greatest_common_divisor = std::gcd(numer, denom);
    numer /= greatest_common_divisor;
    denom /= greatest_common_divisor;

    numer_ = static_cast<int>(numer);
    denom_ = static_cast<int>(denom);
    if (denom_ < 0) {
        numer_ *= -1;
        denom_ *= -1;
    }
    if (numer_ == 0) {
        denom_ = 1;
    }
}

Rational operator+(const Rational& ratio) {
    return ratio;
}

Rational operator-(const Rational& ratio) {
    Rational result = ratio;
    result.SetNumerator(-result.GetNumerator());
    return result;
}

Rational& operator-=(Rational& lhs, const Rational& rhs) {
    lhs += -rhs;
    return lhs;
}

Rational& operator/=(Rational& lhs, const Rational& rhs) {
    lhs *= Rational(rhs.GetDenominator(), rhs.GetNumerator());
    return lhs;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result += rhs;
    return result;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result -= rhs;
    return result;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result *= rhs;
    return result;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational result = lhs;
    result /= rhs;
    return result;
}

Rational operator++(Rational& ratio, int) {
    Rational old = ratio;
    ++ratio;
    return old;
}

Rational operator--(Rational& ratio, int) {
    Rational old = ratio;
    --ratio;
    return old;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() < rhs.GetNumerator() * lhs.GetDenominator();
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs) && lhs != rhs;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    return !(lhs > rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    return !(lhs < rhs);
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return std::make_tuple(lhs.GetNumerator(), lhs.GetDenominator()) ==
           std::make_tuple(rhs.GetNumerator(), rhs.GetDenominator());
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    os << ratio.GetNumerator();
    if (ratio.GetDenominator() != 1) {
        os << "/" << ratio.GetDenominator();
    }
    return os;
}
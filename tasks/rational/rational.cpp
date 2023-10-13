#include "rational.h"
#include <sys/errno.h>
#include <numeric>
#include <tuple>

Rational::Rational() {
    Rational(0);
}

Rational::Rational(int value) {
    this->numer_ = value;
    this->denom_ = 1;
}

Rational::Rational(int numer, int denom) {
    Set(numer, denom);
}

int Rational::GetNumerator() const {
    return this->numer_;
}

int Rational::GetDenominator() const {
    return this->denom_;
}

void Rational::SetNumerator(int value) {
    this->numer_ = value;
    int greatest_common_divisor = std::gcd(GetNumerator(), GetDenominator());
    this->numer_ /= greatest_common_divisor;
    this->denom_ /= greatest_common_divisor;
    if (this->denom_ < 0) {
        this->numer_ *= -1;
        this->denom_ *= -1;
    }
}

void Rational::SetDenominator(int value) {
    if (value == 0) {
        throw RationalDivisionByZero{};
    }
    this->denom_ = value;
    int greatest_common_divisor = std::gcd(GetNumerator(), GetDenominator());
    this->numer_ /= greatest_common_divisor;
    this->denom_ /= greatest_common_divisor;
    if (this->denom_ < 0) {
        this->numer_ *= -1;
        this->denom_ *= -1;
    }
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    lhs.Set(lhs.GetNumerator() * rhs.GetDenominator() + rhs.GetNumerator() * lhs.GetDenominator(), lhs.GetDenominator() * rhs.GetDenominator());
    return lhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    lhs.Set(lhs.GetNumerator() * rhs.GetNumerator(), lhs.GetDenominator() * rhs.GetDenominator());
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
    int numer = 0;
    int denom = 0;
    is >> numer;
    char c = 0;
    is >> c;
    is >> denom;
    ratio.Set(numer, denom);
    return is;
}

// WTF types
void Rational::Set(int64_t numer, int64_t denom) {
    SetNumerator(static_cast<int>(numer));
    SetDenominator(static_cast<int>(denom));
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
    if (rhs.GetNumerator() == 0) {
        throw RationalDivisionByZero{};
    }
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
    return lhs.GetNumerator() * rhs.GetDenominator() <
           rhs.GetNumerator() * lhs.GetDenominator();
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    return lhs.GetNumerator() * rhs.GetDenominator() <
           rhs.GetNumerator() * lhs.GetDenominator() && lhs != rhs;
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
    os << ratio.GetNumerator() << "/" << ratio.GetDenominator();
    return os;
}
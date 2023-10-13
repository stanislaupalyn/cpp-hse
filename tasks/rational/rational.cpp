#include "rational.h"
#include <sys/errno.h>
#include <numeric>

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
}

void Rational::SetDenominator(int value) {
    this->denom_ = value;
}

Rational& operator+=(Rational& lhs, const Rational& rhs) {
    int new_denom = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
    lhs.Set(
        lhs.GetNumerator() * new_denom / lhs.GetDenominator() + rhs.GetNumerator() * new_denom / rhs.GetDenominator(),
        new_denom);
    return lhs;
}

Rational& operator*=(Rational& lhs, const Rational& rhs) {
    int new_numerator = lhs.GetNumerator() * rhs.GetNumerator();
    int new_denominator = lhs.GetDenominator() * rhs.GetDenominator();
    int greatest_common_divisor = std::gcd(new_numerator, new_denominator);
    lhs.Set(new_numerator / greatest_common_divisor, new_denominator / greatest_common_divisor);
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
    return Rational(-ratio.GetNumerator(), ratio.GetDenominator());
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

Rational operator++(Rational& ratio, int x) {
    ratio += x;
    return ratio;
}

Rational operator--(Rational& ratio, int x) {
    ratio -= x;
    return ratio;
}

bool operator<(const Rational& lhs, const Rational& rhs) {
    int new_denom = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
    return lhs.GetNumerator() * new_denom / lhs.GetDenominator() < rhs.GetNumerator() * new_denom / rhs.GetDenominator();
}

bool operator>(const Rational& lhs, const Rational& rhs) {
    int new_denom = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
    return lhs.GetNumerator() * new_denom / lhs.GetDenominator() > rhs.GetNumerator() * new_denom / rhs.GetDenominator();
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
    int new_denom = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
    return lhs.GetNumerator() * new_denom / lhs.GetDenominator() <= rhs.GetNumerator() * new_denom / rhs.GetDenominator();
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
    int new_denom = std::lcm(lhs.GetDenominator(), rhs.GetDenominator());
    return lhs.GetNumerator() * new_denom / lhs.GetDenominator() >= rhs.GetNumerator() * new_denom / rhs.GetDenominator();
}

bool operator==(const Rational& lhs, const Rational& rhs) {
    return std::make_tuple(lhs.GetNumerator(), lhs.GetNumerator()) == std::make_tuple(rhs.GetNumerator(), rhs.GetDenominator());
}

bool operator!=(const Rational& lhs, const Rational& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& os, const Rational& ratio) {
    os << ratio.GetNumerator() << "/" << ratio.GetDenominator();
    return os;
}
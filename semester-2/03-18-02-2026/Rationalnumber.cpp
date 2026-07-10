#include "Rationalnumber.h"

#include <stdexcept>
#include <numeric>

FractionClass::FractionClass(int numerator, int denominator)
{
    if (!denominator)
        throw std::invalid_argument("Denominator cannot be zero!");

    if (denominator < 0)
    {
        denominator = -denominator;
        numerator = -numerator;
    }

    reduce(numerator, denominator);

    this->numerator = numerator;
    this->denominator = denominator;
}

FractionClass FractionClass::operator+(const FractionClass& other) const
{
    return add(*this, other);
}

void FractionClass::addWith(const FractionClass& other)
{
    numerator = numerator * other.denominator +
        other.numerator * denominator;

    denominator *= other.denominator;

    reduce(numerator, denominator);
}

FractionClass FractionClass::add(const FractionClass& lhs, const FractionClass& rhs)
{
    FractionClass result(lhs);
    result.addWith(rhs);
    return result;
}

std::string FractionClass::toString() const
{
    return std::to_string(numerator) + "/" + std::to_string(denominator);
}

void FractionClass::reduce(int& numerator, int& denominator)
{
    int gcd = std::gcd(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
}

#pragma once

#include <string>

class FractionClass
{
public:
    FractionClass(int numerator, int denominator);

    FractionClass operator+(const FractionClass& other) const;

    void addWith(const FractionClass& other);

    static FractionClass add(const FractionClass& lhs, const FractionClass& rhs);

    [[nodiscard]] std::string toString() const;

private:
    int numerator{1};
    int denominator{1};

    static void reduce(int& numerator, int& denominator);
};
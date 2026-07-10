#include <iostream>
#include "Rationalnumber.cpp"

int main()
{
    FractionClass fraction1(1, 2);
    std::cout << "Before reduction: "
        << fraction1.toString() << std::endl;

    FractionClass fraction2(2, 5);

    fraction1.addWith(fraction2);
    std::cout << "After reduction: "
        << fraction1.toString() << std::endl;

    FractionClass result{fraction1 + fraction2};

    FractionClass fraction{FractionClass::add(fraction1, fraction2)};
    std::cout << fraction.toString() << std::endl;

    std::cout << result.toString() << std::endl;
}

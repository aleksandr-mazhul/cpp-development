#include <iostream>
#include <string>
#include <stdexcept>
#include <numeric>
using namespace std;


class FractionClass
{
public:
    FractionClass(int numerator, int denominator)
    {
        if (!denominator)
        {
            throw invalid_argument("Durling, Denominator can not be zero!");
        }

        if (denominator < 0)
        {
            denominator = -denominator;
            numerator = -numerator;
        }

        reduce(numerator, denominator);

        this->numerator = numerator;
        this->denominator = denominator;
    }

    string toString() const
    {
        return to_string(numerator) + "/" + to_string(denominator);
    }

    FractionClass operator+(const FractionClass& other) const
    {
        return add(*this, other);
    }

    void addWith(const FractionClass& other)
    {
        numerator = (numerator * other.denominator + other.numerator * denominator);
        denominator *= other.denominator;
        reduce(numerator, denominator);
    }

    static FractionClass add(const FractionClass& lhs, const FractionClass& rhs)
    {
        FractionClass result(lhs);
        result.addWith(rhs);

        /*auto numerator = (lhs.numerator * rhs.denominator + rhs.numerator * lhs.denominator);
        auto denominator = lhs.denominator*rhs.denominator;
        reduce(numerator, denominator);

        FractionClass result(numerator,denominator);*/

        return result;
    }

private:
    int numerator{1};
    int denominator{1};

    static void reduce(int& numerator, int& denominator)
    {
        int gcd = std::gcd(numerator, denominator);

        denominator /= gcd;
        numerator /= gcd;
    }
};


int main()
{
    FractionClass fraction1(1, 2);
    cout << "Before reduction: " << fraction1.toString() << endl;

    FractionClass fraction2(2, 5);

    fraction1.addWith(fraction2);
    cout << "After reduction: " << fraction1.toString() << endl;

    FractionClass result{fraction1 + fraction2};

    FractionClass fraction{FractionClass::add(fraction1, fraction2)};
    cout << fraction.toString() << endl;
}

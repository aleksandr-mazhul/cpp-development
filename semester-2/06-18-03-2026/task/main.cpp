#include "filters.cpp"
#include " predicates.h"

int main()
{
    IntegerArray numbers{2, 3, 4, -5, 60, 12, -87, 2, 2, 3};
    int value = 2;

    std::array<Predicate, 13> functors{
        NegativePredicate(),
        PositivePredicate(),
        OddPredicate(),
        EvenPredicate(),
        isPositive,
        isNegative,
        isEven,
        isOdd,
        EqualsPredicate(2),
        EqualsPredicate(3),
        RangePredicate(1, 12),
        [](int x) { return x > 0; },
        [value](int x) { return x == value; },
    };

    for (size_t i = 0; i < functors.size(); i++)
    {
        filterByPredicate(numbers, functors[i]);
        std::cout << std::endl;
    }
}
#include " predicates.h"

bool isPositive(int x) { return x > 0; }
bool isNegative(int x) { return x < 0; }
bool isEven(int x) { return !(x % 2); }
bool isOdd(int x) { return x % 2; }

bool isEquals(int x, int value)
{
    return x == value;
}

bool isRangeIn(int x, int up, int down)
{
    return x <= up && x >= down;
}
#pragma once

// функции-предикаты
bool isPositive(int x);
bool isNegative(int x);
bool isEven(int x);
bool isOdd(int x);

bool isEquals(int x, int value);
bool isRangeIn(int x, int up, int down);

// функторы
struct PositivePredicate
{
    bool operator()(int x) const { return x > 0; }
};

struct NegativePredicate
{
    bool operator()(int x) const { return x < 0; }
};

struct OddPredicate
{
    bool operator()(int x) const { return x % 2; }
};

struct EvenPredicate
{
    bool operator()(int x) const { return !(x % 2); }
};

class EqualsPredicate
{
public:
    EqualsPredicate(int value) : value{value}
    {
    }

    bool operator()(int x) const { return x == value; }

private:
    int value;
};

class RangePredicate
{
public:
    RangePredicate(int down, int up) : down{down}, up{up}
    {
    }

    bool operator()(int x) const { return x <= up && x >= down; }

private:
    int down, up;
};

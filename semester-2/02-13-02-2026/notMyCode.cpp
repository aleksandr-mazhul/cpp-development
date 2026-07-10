/**
 * @brief Classifies integer sequences (monotonic, increasing, decreasing, etc.)
 *          using bitmask flags combinable via operator|.
 */

#include <iostream>

using namespace std;

/**
 * @brief Sequence type as a bitmask; flags can be combined with operator|.
 */
enum class TypeOfSequence
{
    None = 0,
    Equals = 1 << 0,
    Less = 1 << 1,
    More = 1 << 2,
};

using enum TypeOfSequence; // C++20: use Less, Equals, More without prefix

/**
 * @brief Prints array elements to cout, space-separated.
 * @param array Pointer to the first element.
 * @param n     Number of elements.
 */
void displayArray(coеnst int*array, size_t n);

/**
 * @brief Builds a TypeOfSequence bitmask from array (Less | More | Equals).
 * @param array Pointer to the first element.
 * @param n     Number of elements.
 * @return Combined flags for the sequence type.
 */
TypeOfSequence getTypeOfSequence(const int* array, size_t n);

/**
 * @brief Returns a string description for the given type mask.
 * @param state Type mask (e.g. Less, Equals, Less|Equals).
 * @return "monotonous", "strictly increasing", "increasing", etc.
 */
string getTypeOfSequence(const TypeOfSequence& state);

/**
 * @brief Bitwise OR for combining TypeOfSequence flags.
 */
constexpr TypeOfSequence operator|(TypeOfSequence lhs, TypeOfSequence rhs);

/**
 * @brief Compound assignment: modifies lhs and returns reference to it.
 */
constexpr TypeOfSequence& operator|=(TypeOfSequence& lhs, TypeOfSequence rhs);

/**
 * @brief Runs test examples for all sequence types.
 */
int main()
{
    cout << "=== Test examples ===" << endl;

    // Monotonic (all equal)
    int a1[] = {5, 5, 5, 5, 5};
    cout << "Sequence ";
    displayArray(a1, 5);
    cout << "is " << getTypeOfSequence(getTypeOfSequence(a1, 5)) << endl;

    // Strictly increasing
    int a2[] = {1, 2, 3, 4, 5};
    cout << "Sequence ";
    displayArray(a2, 5);
    cout << "is " << getTypeOfSequence(getTypeOfSequence(a2, 5)) << endl;

    // Non-strictly increasing
    int a3[] = {1, 2, 2, 3, 4};
    cout << "Sequence ";
    displayArray(a3, 5);
    cout << "is " << getTypeOfSequence(getTypeOfSequence(a3, 5)) << endl;

    // Strictly decreasing
    int a4[] = {5, 4, 3, 2, 1};
    cout << "Sequence ";
    displayArray(a4, 5);
    cout << "is " << getTypeOfSequence(getTypeOfSequence(a4, 5)) << endl;

    // Non-strictly decreasing
    int a5[] = {5, 4, 4, 3, 1};
    cout << "Sequence ";
    displayArray(a5, 5);
    cout << "is " << getTypeOfSequence(getTypeOfSequence(a5, 5)) << endl;

    // Mixed
    int a6[] = {1, 3, 2, 4, 2};
    cout << "Sequence ";
    displayArray(a6, 5);
    cout << "is " << getTypeOfSequence(getTypeOfSequence(a6, 5)) << endl;

    // Single element
    int a7[] = {42};
    cout << "Sequence ";
    displayArray(a7, 1);
    cout << "is " << getTypeOfSequence(getTypeOfSequence(a7, 1)) << endl;
}

void displayArray(const int* array, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        cout << array[i] << " ";
    }
}

TypeOfSequence getTypeOfSequence(const int* array, size_t n)
{
    TypeOfSequence state{None};
    for (size_t i = 0; i < n - 1; i++)
    {
        if (array[i] < array[i + 1])
        {
            state |= Less;
        }
        else if (array[i] > array[i + 1])
        {
            state |= More;
        }
        else
        {
            state |= Equals;
        }
    }
    return state;
}

constexpr TypeOfSequence operator|(TypeOfSequence lhs, TypeOfSequence rhs)
{
    return static_cast<TypeOfSequence>(
        static_cast<int>(lhs) | static_cast<int>(rhs)
    );
}

constexpr TypeOfSequence& operator|=(TypeOfSequence& lhs, TypeOfSequence rhs)
{
    lhs = lhs | rhs;
    return lhs;
}

/**
 * @brief Maps a type mask to a human-readable string name.
 */
string getTypeOfSequence(const TypeOfSequence& state)
{
    switch (state)
    {
    case Equals: return "monotonous";
    case Less: return "strictly increasing";
    case Less | Equals: return "increasing";
    case More: return "strictly decreasing";
    case More | Equals: return "decreasing";
    default: return "unsorted";
    }
}

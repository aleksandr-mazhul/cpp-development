#include "math_utils.h"

#include <iostream>
#include <vector>

std::vector<int> read_numbers()
{
    int count;
    std::cout << "How many numbers? " << std::flush;
    std::cin >> count;

    std::vector<int> nums;

    for (int i = 0; i < count; ++i)
    {
        int value;
        std::cout << "Enter number #" << i + 1 << ": ";
        std::cin >> value;

        nums.push_back(value);
    }

    return nums;
}

int main()
{
    std::cout << "=== Debug Lab ===\n";

    auto nums = read_numbers();

    int total = sum_vector(nums);
    int mx = find_max(nums);
    double avg = average(nums);

    std::cout << "\nResults:\n";
    std::cout << "sum = " << total << "\n";
    std::cout << "max = " << mx << "\n";
    std::cout << "avg = " << avg << "\n";

    int n;
    std::cout << "\nFactorial of: ";
    std::cin >> n;

    int fact = factorial(n);

    std::cout << "factorial = " << fact << "\n";

    return 0;
}

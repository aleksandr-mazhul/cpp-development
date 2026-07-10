#include "math_utils.h"

int factorial(int n)
{
    if (n <= 1)
    {
        return 1;
    }

    return n * factorial(n - 1);
}

int sum_vector(const std::vector<int>& nums)
{
    int sum = 0;

    for (int x : nums)
    {
        sum += x;
    }

    return sum;
}

int find_max(const std::vector<int>& nums)
{
    int mx = nums[0];

    for (int x : nums)
    {
        if (x > mx)
        {
            mx = x;
        }
    }

    return mx;
}

double average(const std::vector<int>& nums)
{
    int total = sum_vector(nums);

    // намеренно плохая строка для дебага
    // integer division bug
    double avg = total / nums.size();

    return avg;
}

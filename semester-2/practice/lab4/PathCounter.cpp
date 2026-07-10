#include "PathCounter.h"

#include "ConsoleColors.h"

#include <iostream>
#include <stdexcept>
#include <vector>

namespace
{
    void validateInput(int n, int k)
    {
        if (n < 0)
        {
            throw std::invalid_argument("ERROR: Длина поля N не может быть отрицательной");
        }
        if (k < 1)
        {
            throw std::invalid_argument("ERROR: Максимальный шаг K должен быть не меньше 1");
        }
    }

    // Рекурсивный перебор всех комбинаций ходов
    void collectPathsRecursive(int remaining, int k, std::vector<int>& current, std::vector<Path>& all)
    {
        if (remaining == 0)
        {
            all.push_back(current);
            return;
        }

        for (int step = 1; step <= k && step <= remaining; ++step)
        {
            current.push_back(step);
            collectPathsRecursive(remaining - step, k, current, all);
            current.pop_back();
        }
    }
}

// Рекурсивный алгоритм
long long countPathsRecursive(int n, int k)
{
    validateInput(n, k);

    if (n == 0)
    {
        return 1;
    }

    long long total = 0;
    for (int step = 1; step <= k && step <= n; ++step)
    {
        total += countPathsRecursive(n - step, k);
    }
    return total;
}

// Нерекурсивный алгоритм (динамическое программирование, цикл)
long long countPathsIterative(int n, int k)
{
    validateInput(n, k);

    std::vector<long long> dp(n + 1, 0);
    dp[0] = 1;

    for (int i = 1; i <= n; ++i)
    {
        for (int step = 1; step <= k && step <= i; ++step)
        {
            dp[i] += dp[i - step];
        }
    }

    return dp[n];
}

std::vector<Path> findAllPaths(int n, int k)
{
    validateInput(n, k);

    std::vector<Path> all;
    std::vector<int> current;
    collectPathsRecursive(n, k, current, all);
    return all;
}

void printPaths(const std::vector<Path>& paths, std::ostream& out, int targetN)
{
    out << Color::magenta << "  Комбинации ходов (" << Color::cyan << paths.size()
        << Color::magenta << "):\n" << Color::reset;

    if (paths.empty())
    {
        out << Color::dim << "    (путей нет)\n" << Color::reset;
        return;
    }

    for (std::size_t i = 0; i < paths.size(); ++i)
    {
        out << Color::cyan << "    " << (i + 1) << ")" << Color::reset << ' ';

        if (paths[i].empty())
        {
            out << Color::blue << "(без ходов)\n" << Color::reset;
            continue;
        }

        int sum = 0;
        for (std::size_t j = 0; j < paths[i].size(); ++j)
        {
            if (j > 0)
            {
                out << Color::dim << " + " << Color::reset;
            }
            out << Color::white << paths[i][j] << Color::reset;
            sum += paths[i][j];
        }

        out << Color::dim << "  =>  " << Color::reset;
        if (targetN >= 0 && sum == targetN)
        {
            out << Color::green << sum << Color::reset;
        }
        else
        {
            out << Color::red << sum << Color::reset;
        }
        out << '\n';
    }
}

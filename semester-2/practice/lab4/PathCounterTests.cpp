#include "PathCounterTests.h"

#include "PathCounter.h"
#include "ConsoleColors.h"

#include <iostream>

namespace
{
    struct TestCase
    {
        int n;
        int k;
        long long expected;
        const char* comment;
        const char* tag; // метка для преподавателя: тип теста
    };

    const TestCase TEST_CASES[] = {
        {3, 2, 3, "Пути: (1,1,1), (2,1), (1,2)", "Пример из условия задачи"},
        {0, 2, 1, "Фишка уже на финише — один пустой путь", "Граничный случай"},
        {5, 1, 1, "Единственная последовательность: 1+1+1+1+1", "Граничный случай"},
        {4, 4, 8, "Восемь различных комбинаций ходов", "Общий случай"},
        {5, 3, 13, "Несколько комбинаций — проверка DP и рекурсии", "Общий случай"},
    };

    constexpr std::size_t TEST_COUNT = sizeof(TEST_CASES) / sizeof(TEST_CASES[0]);

    using CountFn = long long (*)(int, int);

    const char* tagColor(std::size_t testIndex)
    {
        if (testIndex == 0)
        {
            return Color::yellow;
        }
        if (testIndex == 1 || testIndex == 2)
        {
            return Color::blue;
        }
        return Color::magenta;
    }

    void printTestSeparator()
    {
        std::cout << Color::dim << "  ────────────────────────────────────────\n" << Color::reset;
    }

    void runTests(CountFn fn, const char* algorithmName, const char* algorithmColor)
    {
        std::cout << '\n' << Color::yellow << "══════════════════════════════════════════\n"
                  << "  Тесты: " << algorithmColor << algorithmName << Color::yellow
                  << " алгоритм\n"
                  << "══════════════════════════════════════════\n" << Color::reset;

        int passed = 0;
        for (std::size_t i = 0; i < TEST_COUNT; ++i)
        {
            const TestCase& test = TEST_CASES[i];
            const long long result = fn(test.n, test.k);
            const std::vector<Path> paths = findAllPaths(test.n, test.k);
            const bool countOk = result == test.expected;
            const bool pathsOk = paths.size() == test.expected;
            const bool ok = countOk && pathsOk;

            if (ok)
            {
                ++passed;
            }

            printTestSeparator();

            std::cout << (ok ? Color::green : Color::red)
                      << (ok ? "  [OK]  " : " [FAIL] ")
                      << Color::reset
                      << Color::white << "Тест " << (i + 1) << Color::reset
                      << Color::dim << " / " << TEST_COUNT << Color::reset << '\n';

            std::cout << "  " << tagColor(i) << "▸ " << test.tag << Color::reset << '\n';
            std::cout << "  " << Color::cyan << "N = " << test.n << Color::reset
                      << Color::dim << "  |  " << Color::reset
                      << Color::cyan << "K = " << test.k << Color::reset << '\n';
            std::cout << "  " << Color::dim << test.comment << Color::reset << '\n';

            std::cout << "  Число путей: "
                      << Color::yellow << "ожидание " << test.expected << Color::reset
                      << Color::dim << "  →  " << Color::reset
                      << Color::white << algorithmName << " = " << Color::reset;

            if (countOk)
            {
                std::cout << Color::green << result << Color::reset;
            }
            else
            {
                std::cout << Color::red << result << Color::reset
                          << Color::red << " (неверный подсчёт)" << Color::reset;
            }

            if (!pathsOk)
            {
                std::cout << Color::red << "  |  комбинаций: " << paths.size() << Color::reset;
            }
            std::cout << '\n';

            printPaths(paths, std::cout, test.n);
            std::cout << '\n';
        }

        printTestSeparator();
        std::cout << '\n';

        if (passed == TEST_COUNT)
        {
            std::cout << Color::green << "  Итог: все тесты пройдены — "
                      << passed << " из " << TEST_COUNT << Color::reset << '\n';
        }
        else if (passed > 0)
        {
            std::cout << Color::yellow << "  Итог: пройдено " << passed
                      << " из " << TEST_COUNT << Color::reset << '\n';
        }
        else
        {
            std::cout << Color::red << "  Итог: все тесты провалены — 0 из "
                      << TEST_COUNT << Color::reset << '\n';
        }
    }
}

void runRecursiveTests()
{
    runTests(countPathsRecursive, "рекурсивный", Color::cyan);
}

void runIterativeTests()
{
    runTests(countPathsIterative, "нерекурсивный", Color::magenta);
}

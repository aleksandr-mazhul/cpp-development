#include "LinearSystemTests.h"

#include "ConsoleColors.h"
#include "LinearSystem.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

namespace
{
    enum class TestExpect
    {
        Success,
        Error
    };

    struct TestCase
    {
        const char* descFile;
        const char* title;
        const char* tag;
        TestExpect expect;
        int nMatrix;
        int nVector;
        const double* matrix;
        const double* vector;
        const double* expected;
    };

    constexpr const char* TEST_MATRIX_FILE = LAB5_SOURCE_DIR "/tests/test_matrix.bin";
    constexpr const char* TEST_VECTOR_FILE = LAB5_SOURCE_DIR "/tests/test_vector.bin";
    constexpr const char* TEST_RESULT_FILE = LAB5_SOURCE_DIR "/tests/test_result.txt";

    constexpr double MATRIX_3X3[] = {
        2.0, 1.0, -1.0,
        -3.0, -1.0, 2.0,
        -2.0, 1.0, 2.0,
    };
    constexpr double VECTOR_3X3[] = {8.0, -11.0, -3.0};
    constexpr double EXPECTED_3X3[] = {2.0, 3.0, -1.0};

    constexpr double MATRIX_PIVOT[] = {
        0.0, 1.0,
        2.0, 1.0,
    };
    constexpr double VECTOR_PIVOT[] = {2.0, 5.0};
    constexpr double EXPECTED_PIVOT[] = {1.5, 2.0};

    constexpr double MATRIX_2X2[] = {
        1.0, 0.0,
        0.0, 1.0,
    };
    constexpr double VECTOR_2X2[] = {1.0, 2.0};

    constexpr double VECTOR_3[] = {1.0, 2.0, 3.0};

    constexpr double MATRIX_SINGULAR[] = {
        1.0, 1.0,
        2.0, 2.0,
    };
    constexpr double VECTOR_SINGULAR[] = {1.0, 2.0};

    constexpr double MATRIX_INCONSISTENT[] = {
        1.0, 1.0,
        1.0, 1.0,
    };
    constexpr double VECTOR_INCONSISTENT[] = {1.0, 3.0};

    const TestCase TEST_CASES[] = {
        {"01_success_3x3.txt",
         "Успех 3×3",
         "Эталонная система",
         TestExpect::Success,
         3,
         3,
         MATRIX_3X3,
         VECTOR_3X3,
         EXPECTED_3X3},
        {"02_pivot_swap.txt",
         "Выбор главного элемента",
         "Нулевой первый коэффициент, перестановка строк",
         TestExpect::Success,
         2,
         2,
         MATRIX_PIVOT,
         VECTOR_PIVOT,
         EXPECTED_PIVOT},
        {"03_bad_sizes.txt",
         "Разные размеры",
         "Ошибка проверки данных",
         TestExpect::Error,
         2,
         3,
         MATRIX_2X2,
         VECTOR_3,
         nullptr},
        {"04_singular.txt",
         "Вырожденная система",
         "Пропорциональные строки",
         TestExpect::Error,
         2,
         2,
         MATRIX_SINGULAR,
         VECTOR_SINGULAR,
         nullptr},
        {"05_inconsistent.txt",
         "Несовместная система",
         "Параллельные уравнения",
         TestExpect::Error,
         2,
         2,
         MATRIX_INCONSISTENT,
         VECTOR_INCONSISTENT,
         nullptr},
    };

    constexpr std::size_t TEST_COUNT = sizeof(TEST_CASES) / sizeof(TEST_CASES[0]);

    const char* tagColor(std::size_t testIndex)
    {
        if (testIndex == 0)
        {
            return Color::yellow;
        }
        if (testIndex == 1)
        {
            return Color::blue;
        }
        return Color::magenta;
    }

    void printTestLegend()
    {
        std::cout << Color::yellow << "  Легенда:\n" << Color::reset;
        std::cout << "    " << Color::white << "коэффициенты" << Color::reset << Color::dim
                  << " — матрица системы" << Color::reset << '\n';
        std::cout << "    " << Color::cyan << "с.ч." << Color::reset << Color::dim
                  << " — столбец свободных членов" << Color::reset << '\n';
        std::cout << "    " << Color::green << "решение" << Color::reset << Color::dim
                  << " — найденные неизвестные" << Color::reset << '\n';
        std::cout << "    " << Color::red << "ошибка" << Color::reset << Color::dim
                  << " — система не решена" << Color::reset << '\n';
    }

    void printTestSeparator()
    {
        std::cout << Color::dim << "  ────────────────────────────────────────\n" << Color::reset;
    }

    void printTestHeader(const TestCase& test, std::size_t index)
    {
        std::cout << Color::cyan << "  ━━━━━━━━━━ Тест " << (index + 1) << " из " << TEST_COUNT
                  << ": " << test.title << " ━━━━━━━━━━\n" << Color::reset;
        std::cout << "  " << tagColor(index) << "▸ " << test.tag << Color::reset << '\n';
    }

    void printTestDescription(const char* fileName)
    {
        const std::string path = std::string(LAB5_SOURCE_DIR) + "/tests/" + fileName;
        std::ifstream in(path);
        if (!in)
        {
            return;
        }

        std::string line;
        while (std::getline(in, line))
        {
            if (!line.empty() && line[0] == '#')
            {
                std::cout << Color::dim << "  " << line.substr(1) << Color::reset << '\n';
            }
        }
    }

    void printTestAnalysis(const char* message)
    {
        std::cout << Color::yellow << "  Анализ: " << Color::reset << message << '\n';
    }

    void printMismatchedCondition(int nMatrix, const double* matrix, int nVector,
                                  const double* vector)
    {
        std::cout << Color::yellow << "  Исходное условие:\n" << Color::reset;
        std::cout << Color::dim << "  Матрица коэффициентов (" << nMatrix << "×" << nMatrix
                  << "):\n" << Color::reset;
        printSystemTable(nMatrix, matrix, vector);
        std::cout << Color::red << "  Столбец свободных членов: " << nVector << " знач.";
        if (nVector > nMatrix)
        {
            std::cout << " (";
            for (int i = 0; i < nVector; ++i)
            {
                std::cout << vector[i];
                if (i + 1 < nVector)
                {
                    std::cout << ", ";
                }
            }
            std::cout << ')';
        }
        std::cout << Color::reset << '\n';
        std::cout << Color::red << "  Число уравнений и число свободных членов не совпадают.\n"
                  << Color::reset;
    }

    bool nearlyEqual(double a, double b)
    {
        return std::fabs(a - b) < 1e-5;
    }

    bool solutionsMatch(int n, const double* actual, const double* expected)
    {
        for (int i = 0; i < n; ++i)
        {
            if (!nearlyEqual(actual[i], expected[i]))
            {
                return false;
            }
        }
        return true;
    }

    void printExpectedSolution(int n, const double* expected)
    {
        std::cout << Color::yellow << "  Ожидалось: ";
        for (int i = 0; i < n; ++i)
        {
            static const char* const SUBS[] = {"₀", "₁", "₂", "₃", "₄", "₅", "₆", "₇", "₈", "₉"};
            std::cout << 'x' << SUBS[i] << " = " << expected[i];
            if (i + 1 < n)
            {
                std::cout << ", ";
            }
        }
        std::cout << Color::reset << '\n';
    }
}

void runAllTests()
{
    std::cout << '\n' << Color::yellow << "══════════════════════════════════════════\n"
              << "  Автотесты: метод Гаусса (главный элемент)\n"
              << "══════════════════════════════════════════\n" << Color::reset;
    printTestLegend();
    std::cout << '\n';

    int passed = 0;
    for (std::size_t i = 0; i < TEST_COUNT; ++i)
    {
        const TestCase& test = TEST_CASES[i];
        printTestSeparator();
        printTestHeader(test, i);
        printTestDescription(test.descFile);

        if (test.matrix != nullptr && test.nMatrix == test.nVector)
        {
            printSystemEquations(test.nMatrix, test.matrix, test.vector);
            std::cout << Color::dim << "  Таблица коэффициентов:\n" << Color::reset;
            printSystemTable(test.nMatrix, test.matrix, test.vector);
        }
        else if (test.matrix != nullptr)
        {
            printMismatchedCondition(test.nMatrix, test.matrix, test.nVector, test.vector);
        }

        writeMatrixBinary(TEST_MATRIX_FILE, test.nMatrix, test.matrix);
        writeVectorBinary(TEST_VECTOR_FILE, test.nVector, test.vector);

        double solution[MAX_N]{};
        const bool solved = solveSystemGauss(TEST_MATRIX_FILE, TEST_VECTOR_FILE, TEST_RESULT_FILE,
                                             solution, true);

        bool ok = false;
        if (test.expect == TestExpect::Success)
        {
            ok = solved && solutionsMatch(test.nMatrix, solution, test.expected);
            if (solved)
            {
                printSolution(test.nMatrix, solution);
                printTestAnalysis("Метод Гаусса с главным элементом дал единственное решение.");
            }
            else
            {
                printTestAnalysis("Ожидался успех, но программа сообщила об ошибке.");
            }

            if (!ok && test.expected != nullptr)
            {
                printExpectedSolution(test.nMatrix, test.expected);
            }
        }
        else
        {
            ok = !solved;
            printTestAnalysis(ok ? "Как и ожидалось: систему решить нельзя."
                                 : "Ожидалась ошибка, но программа нашла решение.");
        }

        if (ok)
        {
            ++passed;
        }

        std::cout << (ok ? Color::green : Color::red) << (ok ? "  [ПРОЙДЕН]  " : " [ПРОВАЛЕН] ")
                  << Color::reset << Color::white << "Тест " << (i + 1) << Color::reset
                  << Color::dim << " из " << TEST_COUNT << Color::reset << '\n';
    }

    printTestSeparator();
    std::cout << '\n';

    if (passed == static_cast<int>(TEST_COUNT))
    {
        std::cout << Color::green << "  Итог: все тесты пройдены — " << passed << " из "
                  << TEST_COUNT << Color::reset << '\n';
    }
    else if (passed > 0)
    {
        std::cout << Color::yellow << "  Итог: пройдено " << passed << " из " << TEST_COUNT
                  << Color::reset << '\n';
    }
    else
    {
        std::cout << Color::red << "  Итог: все тесты провалены — 0 из " << TEST_COUNT
                  << Color::reset << '\n';
    }
}

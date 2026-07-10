#include "PathCounter.h"
#include "PathCounterTests.h"
#include "ConsoleColors.h"

#include <iostream>

namespace
{
    void runManualInput()
    {
        int n = 0;
        int k = 0;

        std::cout << "Введите длину поля N: ";
        std::cin >> n;
        std::cout << "Введите максимальный шаг K: ";
        std::cin >> k;

        try
        {
            const long long recursiveResult = countPathsRecursive(n, k);
            const long long iterativeResult = countPathsIterative(n, k);
            const std::vector<Path> paths = findAllPaths(n, k);

            std::cout << '\n' << Color::yellow << "=== Результат для "
                      << Color::cyan << "N = " << n << Color::yellow << ", "
                      << Color::cyan << "K = " << k << Color::yellow << " ===\n"
                      << Color::reset;

            std::cout << Color::cyan << "  Рекурсивный алгоритм:   " << Color::reset;
            std::cout << Color::green << recursiveResult << Color::dim << " путей\n" << Color::reset;

            std::cout << Color::magenta << "  Нерекурсивный алгоритм: " << Color::reset;
            std::cout << Color::green << iterativeResult << Color::dim << " путей\n" << Color::reset;

            if (recursiveResult != iterativeResult)
            {
                std::cout << Color::red << "  Внимание: алгоритмы дали разные ответы!\n" << Color::reset;
            }
            else
            {
                std::cout << Color::green << "  Алгоритмы совпали.\n" << Color::reset;
            }

            printPaths(paths, std::cout, n);
        }
        catch (const std::invalid_argument& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}

int main()
{
    int choice = -1;

    while (choice != 0)
    {
        std::cout << "\033[1;33m\n=== Лаб. 4: Число путей фишки (рекурсия + цикл) ===\033[0m\n";
        std::cout << "\033[1;36m1. Ввод N и K с клавиатуры (оба алгоритма)\n"
                  << "2. Запустить тесты рекурсивного алгоритма\n"
                  << "3. Запустить тесты нерекурсивного алгоритма\n"
                  << "0. Выход\033[0m\n"
                  << "Ваш выбор: ";

        std::cin >> choice;

        switch (choice)
        {
        case 1:
            runManualInput();
            break;
        case 2:
            runRecursiveTests();
            break;
        case 3:
            runIterativeTests();
            break;
        case 0:
            std::cout << "\033[1;33mВыход.\033[0m\n";
            break;
        default:
            std::cout << "\033[1;31mНеверный пункт меню.\033[0m\n";
            break;
        }
    }

    return 0;
}

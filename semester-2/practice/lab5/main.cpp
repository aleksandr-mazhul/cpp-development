#include "LinearSystem.h"
#include "LinearSystemTests.h"
#include "ConsoleColors.h"

#include <iostream>

int main()
{
    int choice = -1;

    while (choice != 0)
    {
        std::cout << Color::yellow << "\n=== Лаб. 5: СЛАУ методом Гаусса ===\n" << Color::reset;
        std::cout << Color::cyan << "1. Создать бинарные файлы\n"
                  << "2. Просмотреть бинарные файлы\n"
                  << "3. Решить СЛАУ\n"
                  << "4. Автотесты\n"
                  << "0. Выход\n"
                  << Color::reset << "Ваш выбор: ";

        std::cin >> choice;

        switch (choice)
        {
        case 1:
            createBinaryFiles();
            break;
        case 2:
            viewBinaryFiles();
            break;
        case 3:
        {
            int n = 0;
            if (!readSize(DEFAULT_MATRIX_FILE, n))
            {
                std::cerr << Color::red << "Ошибка: сначала создайте файлы (пункт 1).\n"
                          << Color::reset;
                break;
            }

            double solution[MAX_N]{};
            if (solveSystemGauss(DEFAULT_MATRIX_FILE, DEFAULT_VECTOR_FILE, DEFAULT_RESULT_FILE,
                                 solution))
            {
                printSolution(n, solution);
                viewResultFile();
            }
            else
            {
                std::cout << Color::red << "Систему решить не удалось.\n" << Color::reset;
            }
            break;
        }
        case 4:
            runAllTests();
            break;
        case 0:
            std::cout << Color::yellow << "Выход.\n" << Color::reset;
            break;
        default:
            std::cout << Color::red << "Неверный пункт меню.\n" << Color::reset;
            break;
        }
    }

    return 0;
}

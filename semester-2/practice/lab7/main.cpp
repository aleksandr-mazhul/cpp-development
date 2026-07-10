#include "Comparators.h"
#include "ConsoleColors.h"
#include "StudentList.h"
#include "StudentListTests.h"

#include <iostream>

namespace
{
    bool requireNonEmpty(const StudentList& list)
    {
        if (!list.isEmpty())
        {
            return true;
        }

        std::cout << Color::red << "Ошибка: список пуст. Сначала создайте список (пункт 1).\n"
                  << Color::reset;
        return false;
    }
}

int main()
{
    StudentList students;
    int choice = -1;

    while (choice != 0)
    {
        std::cout << Color::yellow << "\n=== Лаб. 7: Однонаправленный список студентов ===\n" << Color::reset;
        std::cout << Color::cyan << "1. Создать список (ввод с клавиатуры)\n"
                  << "2. Просмотреть список\n"
                  << "3. Сортировать по среднему баллу\n"
                  << "4. Вставить студента (с сохранением порядка)\n"
                  << "5. Автотесты\n"
                  << "0. Выход\n"
                  << Color::reset << "Ваш выбор: ";
        std::cin >> choice;

        try
        {
            switch (choice)
            {
            case 1:
                students.createFromKeyboard();
                std::cout << Color::green << "\nСписок создан.\n" << Color::reset;
                std::cout << Color::blue << "--- Текущий список ---\n" << Color::reset;
                students.printColored(std::cout);
                break;
            case 2:
                if (!requireNonEmpty(students))
                {
                    break;
                }
                std::cout << Color::blue << "\n--- Список студентов ---\n" << Color::reset;
                students.printColored(std::cout);
                break;
            case 3:
                if (!requireNonEmpty(students))
                {
                    break;
                }
                {
                    std::cout << Color::magenta << "\nПорядок сортировки:\n" << Color::reset;
                    auto compare = readAverageComparatorFromKeyboard();
                    students.sortByAverage(compare);
                    std::cout << Color::green << "\nСписок отсортирован " << comparatorLabel(compare)
                              << ".\n" << Color::reset;
                    std::cout << Color::blue << "--- Результат сортировки ---\n" << Color::reset;
                    students.printColored(std::cout);
                }
                break;
            case 4:
                {
                    std::cout << Color::magenta << "\nПорядок вставки (должен совпадать с текущей сортировкой списка):\n"
                              << Color::reset;
                    auto compare = readAverageComparatorFromKeyboard();
                    students.insertSortedFromKeyboard(compare);
                    std::cout << Color::green << "\nСтудент вставлен с сохранением порядка ("
                              << comparatorLabel(compare) << ").\n" << Color::reset;
                    std::cout << Color::blue << "--- Список после вставки ---\n" << Color::reset;
                    students.printColored(std::cout);
                }
                break;
            case 5:
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
        catch (const std::exception& e)
        {
            std::cerr << Color::red << e.what() << '\n' << Color::reset;
        }
    }

    return 0;
}

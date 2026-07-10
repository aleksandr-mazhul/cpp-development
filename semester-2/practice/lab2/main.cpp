#include "Matrix.h"

#include <iostream>

int main()
{
    int choice = -1;

    while (choice != 0)
    {
        std::cout << "\033[1;33m\n=== Лаб. 2: Статическая матрица ===\033[0m\n";
        std::cout << "\033[1;36m1. Загрузить матрицу из файла matrix.txt\n"
                  << "2. Ввод матрицы с клавиатуры (интерактивная сетка) и сохранение в matrix.txt\n"
                  << "3. Вывести матрицу на экран\n"
                  << "4. Задание 5: вставить нулевую строку после последней убывающей строки "
                     "с максимальным числом элементов с чётной минимальной цифрой\n"
                  << "5. Запустить все тесты из папки tests/\n"
                  << "0. Выход\033[0m\n"
                  << "Ваш выбор: ";

        std::cin >> choice;

        switch (choice)
        {
        case 1:
            loadMatrixFromFile();
            break;
        case 2:
            inputMatrixFromKeyboardAndSave();
            break;
        case 3:
            if (rowCount > 0 && colCount > 0)
            {
                std::cout << "\033[1;34m\nМатрица:\033[0m\n";
                printMatrix(-1, -1);
            }
            else
            {
                std::cout << "\033[1;31mОшибка: матрица не загружена. Сначала выберите пункт 1 или 2.\033[0m\n";
            }
            break;
        case 4:
            insertZeroRowTask();
            break;
        case 5:
            runAllTests();
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

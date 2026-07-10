#include "WordArray.h"

#include <iostream>

int main()
{
    WordArray words;
    int choice = -1;

    while (choice != 0)
    {
        std::cout << "\033[1;33m\n=== Лаб. 3: Массив указателей на строки (вар. 5) ===\033[0m\n";
        std::cout << "\033[1;36m1. Ввести текст и выполнить задание\n"
                  << "2. Запустить автотесты\n"
                  << "0. Выход\033[0m\n"
                  << "Ваш выбор: ";

        std::cin >> choice;

        switch (choice)
        {
        case 1:
            words.inputTextFromKeyboard();
            words.runTask();
            break;
        case 2:
            words.runAllTests();
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

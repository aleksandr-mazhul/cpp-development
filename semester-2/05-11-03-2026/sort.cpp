#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>

constexpr int SizeMenuFunction{4};
constexpr int KeyUp{72};
constexpr int KeyDown{80};
constexpr int KeyEnter{13};
constexpr int SpecialKeyPrefix1{0};
constexpr int SpecialKeyPrefix2{224};

using Sorting = void (*)(int* const, int, int);

int* initArray(int size);
void printArray(const int* arr, int size);
void sortArray(Sorting);
void quickSort(int* const arr, int left, int right);
void bubbleSort(int* const arr, int left, int right);
void selectionSort(int* const arr, int left, int right);
void insertionSort(int* const arr, int left, int right);
int textBar(const char* menuOptions[], int numOptions);
void choiceMenuOption(int& keyCode, int& choice, int numOptions);
void menu(int numOptions, int choice, const char* menuOptions[]);
void setConsoleColor(int color);

int getch();

/*
void setConsoleColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}*/

void setConsoleColor(int)
{
    // stub for portability
}

int getch()
{
    termios oldt{};
    termios newt{};
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main()
{
    /*const char* menu[]{ "Quick Sort", "Bubble Sort", "Selection Sort", "Insertion Sort", "Exit" };
	Sorting sortFunctions[SizeMenuFunction]{ quickSort, bubbleSort, selectionSort, insertionSort };

	int numOptions{ sizeof(menu) / sizeof(menu[0]) };
	while (true)
	{
		int choice{ textBar(menu, numOptions) };
		if (choice == SizeMenuFunction)
		{
			return 0;
		}
		sortArray(sortFunctions[choice]);
	}*/

    /*
    std::cout <<(void*)quickSort << std::endl;
    std::cout <<(void*)insertionSort << std::endl;
    std::cout <<(void*)selectionSort << std::endl;
    std::cout <<(void*)bubbleSort << std::endl;
    */

    /*auto pf1{quickSort};
    auto pf2{bubbleSort};
    auto pf3{selectionSort};
    auto pf4{insertionSort};*/


    /*int option{ 0 };
    std::cin >> option;
    std::cout << "entet option";*/
    sortArray(quickSort);
    sortArray(insertionSort);
    sortArray(bubbleSort);
    sortArray(selectionSort);

    std::cout << std::endl;
}

int* initArray(int size)
{
    int* const arr{new int[size]};
    for (int i{0}; i < size; i++)
    {
        arr[i] = size / 2 - i;
    }
    return arr;
}

void printArray(const int* const arr, const int size)
{
    for (int i{0}; i < size; i++)
    {
        std::cout.width(6);
        std::cout << arr[i];
    }
    std::cout << std::endl;
}

void sortArray(const Sorting sorting)
{
    system("cls");
    int size;
    std::cout << "Enter the size of the array: ";
    std::cin >> size;

    int* arr{initArray(size)};
    std::cout << "\nOriginal Array:\n";
    printArray(arr, size);

    sorting(arr, 0, size - 1);

    quickSort(arr, 0, size - 1);

    std::cout << "\nSorted Array:\n";
    printArray(arr, size);

    delete[] arr;
    std::cout << "\nPress any key to return to the menu...";
    system("pause");
}

void quickSort(int* const arr, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int pivot{arr[(left + right) / 2]};
    int i{left}, j{right};
    while (i <= j)
    {
        while (arr[i] < pivot)
        {
            i++;
        }
        while (arr[j] > pivot)
        {
            j--;
        }
        if (i <= j)
        {
            std::swap(arr[i], arr[j]);
            i++, j--;
        }
    }
    quickSort(arr, left, j);
    quickSort(arr, i, right);
}

void bubbleSort(int* const arr, int left, int right)
{
    for (int i{left}; i < right; i++)
    {
        for (int j{right}; j > i; j--)
        {
            if (arr[j] < arr[j - 1])
            {
                std::swap(arr[j], arr[j - 1]);
            }
        }
    }
}

void selectionSort(int* const arr, int left, int right)
{
    for (int i{left}; i < right; i++)
    {
        int minIndex{i};
        for (int j{i + 1}; j <= right; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        std::swap(arr[i], arr[minIndex]);
    }
}

void insertionSort(int* const arr, int left, int right)
{
    for (int i{left + 1}; i <= right; i++)
    {
        int key{arr[i]};
        int j{i - 1};
        while (j >= left && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int textBar(const char* menuOptions[], int numOptions)
{
    int choice{0};
    int keyCode{0};

    do
    {
        std::cout << "\033[2J\033[H";
        menu(numOptions, choice, menuOptions);
        choiceMenuOption(keyCode, choice, numOptions);
    }
    while (keyCode != KeyEnter);

    return choice;
}

void choiceMenuOption(int& keyCode, int& choice, int numOptions)
{
    keyCode = getch();
    if (keyCode == SpecialKeyPrefix1 || keyCode == SpecialKeyPrefix2)
    {
        keyCode = getch();
        if (keyCode == KeyUp)
        {
            choice = (choice > 0) ? choice - 1 : numOptions - 1;
        }
        else if (keyCode == KeyDown)
        {
            choice = (choice < numOptions - 1) ? choice + 1 : 0;
        }
    }
}

void menu(int numOptions, int choice, const char* menuOptions[])
{
    for (int i{0}; i < numOptions; i++)
    {
        if (i == choice)
        {
            setConsoleColor(5);
            std::cout << "> " << menuOptions[i] << " <" << std::endl;
            setConsoleColor(7);
        }
        else
        {
            std::cout << "  " << menuOptions[i] << std::endl;
        }
    }
}

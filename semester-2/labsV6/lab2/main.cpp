#include "string_utils.cpp"


#include <iostream>
#include <locale>

using namespace std;

int main()
{
    locale::global(locale(""));
    wcin.imbue(locale());
    wcout.imbue(locale());

    constexpr int StrLen = 100;
    auto str = new wchar_t[StrLen];

    wcout << L"Введите строку: ";
    wcin.getline(str, StrLen);

    wcout << geometricMeanOddLowercase(str) << endl;
    wcout << lengthFirstWordEndingWithConsonant(str) << endl;
    wcout << countOfWordsWithRussianLetter(str) << endl;

    delete[] str;

    runTests();
}

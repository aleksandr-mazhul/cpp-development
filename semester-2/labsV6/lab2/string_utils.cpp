#include "string_utils.h"

#include <iostream>
#include <string>
using namespace std;
#include <cmath>

bool isLowercase(wchar_t c)
{
    return c >= L'a' && c <= L'z';
}

bool isUppercase(wchar_t c)
{
    return c >= L'A' && c <= L'Z';
}

bool isEnglish(wchar_t c)
{
    return isLowercase(c) || isUppercase(c);
}

bool isOdd(wchar_t c)
{
    return c % 2 != 0;
}

bool isEven(wchar_t c)
{
    return c % 2 == 0;
}

bool isRussian(wchar_t c)
{
    return (c >= L'А' && c <= L'Я') || (c >= L'а' && c <= L'я') || c == L'Ё' || c == L'ё';
}

bool isVowel(wchar_t c)
{
    constexpr wchar_t vowels[] = L"aeiouyAEIOUY";
    return isInArray(c, vowels);
}

bool isSeparator(wchar_t c)
{
    constexpr wchar_t separators[] = L" ,.;:!?-\t\n";
    return isInArray(c, separators);
}

bool isInArray(wchar_t c, const wchar_t* arr)
{
    for (int i = 0; arr[i] != L'\0'; i++)
    {
        if (c == arr[i])
            return true;
    }
    return false;
}

int findEndOfWordFromPos(const wchar_t* str, int pos)
{
    for (int i = pos; str[i] != L'\0'; i++)
    {
        if (!isSeparator(str[i]) && (isSeparator(str[i + 1]) || str[i + 1] == L'\0'))
        {
            return i;
        }
    }
    return -1;
}

int findStartOfWordFromPos(const wchar_t* str, int pos)
{
    for (int i = pos; i >= 0; i--)
    {
        if (i == 0)
        {
            return 0;
        }

        if (isSeparator(str[i - 1]) && isEnglish(str[i]))
        {
            return i;
        }
    }
    return 0;
}

int findFirstRussianFromPos(const wchar_t* str, int pos)
{
    for (int i = pos; str[i] != L'\0'; i++)
    {
        if (isRussian(str[i]))
        {
            return i;
        }
    }
    return -1;
}

int geometricMeanOddLowercase(const wchar_t* str)
{
    double product = 1;
    int count = 0;
    for (int i = 0; str[i] != L'\0'; i++)
    {
        wchar_t c = str[i];
        if (isEnglish(c) && isLowercase(c) && isOdd(c))
        {
            product *= static_cast<int>(c);
            count++;
        }
    }
    if (count == 0)
    {
        return 0;
    }
    return static_cast<int>(pow(product, 1.0 / count));
}

int lengthFirstWordEndingWithConsonant(const wchar_t* str)
{
    int end = findEndOfWordFromPos(str, 0);

    while (end != -1)
    {
        if (isEnglish(str[end]) && !isVowel(str[end]))
        {
            int start = findStartOfWordFromPos(str, end);
            return end - start + 1;
        }
        end = findEndOfWordFromPos(str, end + 1);
    }
    return -1;
}

int countOfWordsWithRussianLetter(const wchar_t* str)
{
    int count = 0;
    int pos = 0;

    while (true)
    {
        int i = findFirstRussianFromPos(str, pos);

        if (i == -1)
            break;

        int end = findEndOfWordFromPos(str, i);

        if (end == -1)
            break;

        count++;

        pos = end + 1;
    }

    return count;
}

void runTests()
{
    wcout << L"===== TESTING =====" << endl << endl;

    // --- Test 1 ---
    wchar_t test1[] = L"abc def ghi";
    wcout << L"[Test 1] geometricMeanOddLowercase" << endl;
    wcout << L"Input: " << test1 << endl;
    wcout << L"Expected: (depends on odd lowercase letters: a=97, c=99, e=101, g=103, i=105)"
        << endl;
    wcout << L"Actual: " << geometricMeanOddLowercase(test1) << endl;
    wcout << L"--------------------------" << endl;

    // --- Test 2 ---
    wchar_t test2[] = L"apple dog tree";
    wcout << L"[Test 2] lengthFirstWordEndingWithConsonant" << endl;
    wcout << L"Input: " << test2 << endl;
    wcout << L"Expected: 3 (\"dog\")" << endl;
    wcout << L"Actual: " << lengthFirstWordEndingWithConsonant(test2) << endl;
    wcout << L"--------------------------" << endl;

    // --- Test 3 ---
    wchar_t test3[] = L"abc тест hello мир";
    wcout << L"[Test 3] countOfWordsWithRussianLetter" << endl;
    wcout << L"Input: " << test3 << endl;
    wcout << L"Expected: 2 (\"тест\", \"мир\")" << endl;
    wcout << L"Actual: " << countOfWordsWithRussianLetter(test3) << endl;
    wcout << L"--------------------------" << endl;
}

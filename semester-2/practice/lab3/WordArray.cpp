#include "WordArray.h"

#include <cctype>
#include <cstring>
#include <iostream>
#include <limits>
#include <string>

namespace
{
const int INITIAL_CAPACITY = 8;

struct TestCase
{
    const char* name;
    const char* comment;
    const char* text;
    const char* const* expected;
    int expectedCount;
};

const char* const EXPECTED_TEST_1[] = {"hi", "rhythm", "education"};
const char* const EXPECTED_TEST_2[] = {"ant", "is", "dog", "fun"};
const char* const EXPECTED_TEST_3[] = {"amber", "apple"};
const char* const EXPECTED_TEST_4[] = {"myth", "rhythm", "syzygy"};
const char* const EXPECTED_TEST_5[] = {"is", "world", "fun", "hello", "programming"};

void printTestHeader(const char* name, const char* comment, int index, int total)
{
    std::cout << "\033[1;36m\n━━━━━━━━━━ Тест " << index << " / " << total << ": " << name
              << " ━━━━━━━━━━\033[0m\n";
    std::cout << "\033[0;37m  " << comment << "\033[0m\n";
}
} // namespace

WordArray::WordArray() : text(nullptr), words(nullptr), wordCount(0), wordCapacity(0) {}

WordArray::~WordArray()
{
    clear();
}

void WordArray::clear()
{
    freeWords();
    freeText();
    wordCount = 0;
    wordCapacity = 0;
}

void WordArray::freeWords()
{
    if (words == nullptr)
        return;

    // освобождаем каждую строку, на которую указывает элемент массива
    for (int i = 0; i < wordCount; ++i)
        delete[] words[i];

    // освобождаем сам динамический массив указателей
    delete[] words;
    words = nullptr;
}

void WordArray::freeText()
{
    delete[] text;
    text = nullptr;
}

void WordArray::setText(const char* src)
{
    freeWords();
    freeText();
    wordCount = 0;

    if (src == nullptr || src[0] == '\0')
        return;

    const std::size_t len = std::strlen(src);
    text = new char[len + 1];
    std::strcpy(text, src);
}

void WordArray::ensureWordCapacity()
{
    if (wordCount < wordCapacity)
        return;

    const int newCapacity = (wordCapacity == 0) ? INITIAL_CAPACITY : wordCapacity * 2;
    // расширяем динамический массив указателей char**
    char** newWords = new char*[newCapacity];

    // копируем старые указатели (сами строки не копируются)
    for (int i = 0; i < wordCount; ++i)
        newWords[i] = words[i];

    delete[] words;
    words = newWords;
    wordCapacity = newCapacity;
}

bool WordArray::isEnglishLetter(char c)
{
    return std::isalpha(static_cast<unsigned char>(c)) != 0;
}

bool WordArray::isVowel(char c)
{
    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y';
}

int WordArray::countVowels(const char* word)
{
    int count = 0;

    for (const char* p = word; *p != '\0'; ++p)
    {
        if (isVowel(*p))
            ++count;
    }

    return count;
}

char WordArray::firstVowel(const char* word)
{
    for (const char* p = word; *p != '\0'; ++p)
    {
        if (isVowel(*p))
            return static_cast<char>(std::tolower(static_cast<unsigned char>(*p)));
    }

    return '\0';
}

bool WordArray::compareWords(const char* a, const char* b)
{
    const int vowelsA = countVowels(a);
    const int vowelsB = countVowels(b);

    if (vowelsA != vowelsB)
        return vowelsA < vowelsB;

    const char firstA = firstVowel(a);
    const char firstB = firstVowel(b);

    if (firstA != firstB)
        return firstA < firstB;

    return std::strcmp(a, b) < 0;
}

void WordArray::swapWords(int i, int j)
{
    // перестановка строк через обмен указателей в массиве (без копирования текста)
    char* temp = words[i];
    words[i] = words[j];
    words[j] = temp;
}

void WordArray::printLegend() const
{
    std::cout << "\033[0;36m  Легенда:\033[0m "
              << "\033[1;35mгласная\033[0m — первая (ключ при равном числе гласных)  |  "
              << "\033[1;36mгласная\033[0m — остальные (учитываются в подсчёте)\n";
}

void WordArray::printWordHighlighted(const char* word) const
{
    bool firstVowelSeen = false;

    for (const char* p = word; *p != '\0'; ++p)
    {
        if (!isVowel(*p))
        {
            std::cout << *p;
            continue;
        }

        if (!firstVowelSeen)
        {
            std::cout << "\033[1;35m" << *p << "\033[0m";
            firstVowelSeen = true;
        }
        else
        {
            std::cout << "\033[1;36m" << *p << "\033[0m";
        }
    }
}

void WordArray::printTextHighlighted() const
{
    if (text == nullptr)
        return;

    const char* p = text;

    while (*p != '\0')
    {
        if (!isEnglishLetter(*p))
        {
            std::cout << *p;
            ++p;
            continue;
        }

        const char* wordStart = p;

        while (*p != '\0' && isEnglishLetter(*p))
            ++p;

        char buffer[256];
        const int len = static_cast<int>(p - wordStart);
        const int copyLen = (len < 255) ? len : 255;

        for (int i = 0; i < copyLen; ++i)
            buffer[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(wordStart[i])));

        buffer[copyLen] = '\0';
        printWordHighlighted(buffer);
    }
}

void WordArray::printWordsList(bool showIndex) const
{
    if (wordCount == 0)
    {
        std::cout << "\033[1;33mСписок слов пуст.\033[0m\n";
        return;
    }

    for (int i = 0; i < wordCount; ++i)
    {
        if (showIndex)
            std::cout << "\033[1;33m" << (i + 1) << ".\033[0m ";

        // обращение к слову через указатель words[i]
        printWordHighlighted(words[i]);

        std::cout << "  \033[0;36m[count=" << countVowels(words[i]) << "]\033[0m\n";
    }
}

void WordArray::inputTextFromKeyboard()
{
    clear();

    std::cout << "\033[1;36mВведите текст (пустая строка завершает ввод):\033[0m\n";

    std::string line;
    std::string fullText;
    bool firstLine = true;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (std::getline(std::cin, line))
    {
        if (line.empty())
            break;

        if (!firstLine)
            fullText += '\n';

        fullText += line;
        firstLine = false;
    }

    if (fullText.empty())
    {
        std::cout << "\033[1;31mТекст не введён.\033[0m\n";
        return;
    }

    setText(fullText.c_str());
}

void WordArray::extractWords()
{
    freeWords();
    wordCount = 0;

    if (text == nullptr || text[0] == '\0')
        return;

    const char* p = text;

    // выделяем слова из текста и заполняем динамический массив указателей words
    while (*p != '\0')
    {
        while (*p != '\0' && !isEnglishLetter(*p))
            ++p;

        if (*p == '\0')
            break;

        const char* start = p;

        while (*p != '\0' && isEnglishLetter(*p))
            ++p;

        const int len = static_cast<int>(p - start);
        // каждое слово — отдельная динамическая строка
        char* word = new char[len + 1];

        for (int i = 0; i < len; ++i)
            word[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(start[i])));

        word[len] = '\0';

        ensureWordCapacity();
        // сохраняем указатель на строку в динамическом массиве words
        words[wordCount] = word;
        ++wordCount;
    }
}

void WordArray::mergeRanges(int left, int mid, int right)
{
    const int n1 = mid - left + 1;
    const int n2 = right - mid;

    // временные массивы указателей для слияния (копируются только адреса строк)
    char** leftPart = new char*[n1];
    char** rightPart = new char*[n2];

    for (int i = 0; i < n1; ++i)
        leftPart[i] = words[left + i];

    for (int j = 0; j < n2; ++j)
        rightPart[j] = words[mid + 1 + j];

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (compareWords(leftPart[i], rightPart[j]))
            words[k++] = leftPart[i++]; // меняем порядок указателей в words
        else
            words[k++] = rightPart[j++];
    }

    while (i < n1)
        words[k++] = leftPart[i++];

    while (j < n2)
        words[k++] = rightPart[j++];

    delete[] leftPart;
    delete[] rightPart;
}

void WordArray::mergeSortRange(int left, int right)
{
    if (left >= right)
        return;

    if (left + 1 == right)
    {
        if (!compareWords(words[left], words[right]))
            swapWords(left, right); // обмен двух указателей в массиве

        return;
    }

    const int mid = left + (right - left) / 2;

    mergeSortRange(left, mid);
    mergeSortRange(mid + 1, right);
    mergeRanges(left, mid, right);
}

void WordArray::sortWords()
{
    if (wordCount <= 1)
        return;

    // сортировка слиянием по массиву указателей char**
    mergeSortRange(0, wordCount - 1);
}

bool WordArray::matchesExpected(const char* const* expected, int expectedCount) const
{
    if (wordCount != expectedCount)
        return false;

    for (int i = 0; i < expectedCount; ++i)
    {
        if (std::strcmp(words[i], expected[i]) != 0)
            return false;
    }

    return true;
}

void WordArray::processTask(bool showBeforeSort, bool showLegend)
{
    if (text == nullptr)
    {
        std::cout << "\033[1;31mОшибка: текст не задан.\033[0m\n";
        return;
    }

    if (showLegend)
        printLegend();

    std::cout << "\033[1;34m\nИсходный текст:\033[0m\n";
    printTextHighlighted();
    std::cout << '\n';

    extractWords();

    if (wordCount == 0)
    {
        std::cout << "\033[1;31mВ тексте нет английских слов.\033[0m\n";
        return;
    }

    if (showBeforeSort)
    {
        std::cout << "\033[1;34m\nСлова до сортировки:\033[0m\n";
        printWordsList(true);
    }

    sortWords();

    std::cout << "\033[1;34m\nСлова после сортировки (слияние):\033[0m\n";
    printWordsList(true);
}

void WordArray::runTask()
{
    processTask(true);
}

void WordArray::runAllTests()
{
    const TestCase tests[] = {
        {"Сортировка по числу гласных",
         "Первый ключ — count: hi(1) и rhythm(1) раньше education(5).",
         "hi education rhythm",
         EXPECTED_TEST_1,
         3},
        {"Сортировка по первой гласной",
         "При равном count=1 порядок по первой гласной: a < i < o < u → ant, is, dog, fun.",
         "dog ant fun is",
         EXPECTED_TEST_2,
         4},
        {"Сортировка по слову при равных ключах",
         "count и первая гласная совпадают (amber, apple: 2, a) — сравнение по strcmp.",
         "apple amber",
         EXPECTED_TEST_3,
         2},
        {"Буква y как гласная",
         "y входит в count; syzygy имеет 3 гласные (y,y,y) и идёт после myth и rhythm.",
         "myth syzygy rhythm",
         EXPECTED_TEST_4,
         3},
        {"Многострочный текст, регистр и пунктуация",
         "Слова приводятся к нижнему регистру; ! и , не входят в слово; проверка полного pipeline.",
         "Hello, world!\nProgramming IS fun.",
         EXPECTED_TEST_5,
         5},
    };

    const int testCount = static_cast<int>(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;

    std::cout << "\033[1;33m\n========== Запуск автотестов (" << testCount << " шт.) ==========\033[0m\n";
    printLegend();

    for (int t = 0; t < testCount; ++t)
    {
        const TestCase& test = tests[t];
        printTestHeader(test.name, test.comment, t + 1, testCount);

        clear();
        setText(test.text);

        processTask(false, false);

        const bool ok = matchesExpected(test.expected, test.expectedCount);

        if (ok)
        {
            std::cout << "\033[1;32mРезультат: ПРОЙДЕН\033[0m\n";
            ++passed;
        }
        else
        {
            std::cout << "\033[1;31mРезультат: ПРОВАЛ\033[0m\n";
            std::cout << "\033[0;37mОжидалось:\033[0m ";

            for (int i = 0; i < test.expectedCount; ++i)
            {
                if (i > 0)
                    std::cout << ", ";

                std::cout << test.expected[i];
            }

            std::cout << '\n';
        }
    }

    std::cout << "\033[1;33m\n========== Итог: " << passed << " / " << testCount
              << " тестов пройдено ==========\033[0m\n";
}

#pragma once

class WordArray
{
public:
    WordArray();
    ~WordArray();

    WordArray(const WordArray&) = delete;
    WordArray& operator=(const WordArray&) = delete;

    void clear();
    void inputTextFromKeyboard();
    void runTask();
    void runAllTests();

private:
    char* text;
    char** words;       // динамический массив указателей на строки (слова)
    int wordCount;      // текущее число слов в массиве
    int wordCapacity;   // выделенная ёмкость массива указателей

    void freeWords();
    void freeText();
    void ensureWordCapacity();
    void setText(const char* src);

    static bool isEnglishLetter(char c);
    static bool isVowel(char c);
    static int countVowels(const char* word);
    static char firstVowel(const char* word);
    static bool compareWords(const char* a, const char* b);

    void extractWords();
    void sortWords();
    void swapWords(int i, int j);

    void processTask(bool showBeforeSort, bool showLegend = true);
    void printLegend() const;
    void printTextHighlighted() const;
    void printWordHighlighted(const char* word) const;
    void printWordsList(bool showIndex) const;

    void mergeSortRange(int left, int right);
    void mergeRanges(int left, int mid, int right);

    bool matchesExpected(const char* const* expected, int expectedCount) const;
};

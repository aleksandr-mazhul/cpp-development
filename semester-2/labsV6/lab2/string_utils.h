#pragma once

bool isLowercase(wchar_t c);

bool isUppercase(wchar_t c);

bool isEnglish(wchar_t c);

bool isOdd(wchar_t c);

bool isEven(wchar_t c);

bool isRussian(wchar_t c);

bool isVowel(wchar_t c);

bool isSeparator(wchar_t c);


bool isInArray(wchar_t c, const wchar_t* arr);

int findEndOfWordFromPos(const wchar_t* str, int pos);

int findStartOfWordFromPos(const wchar_t* str, int pos);

int findFirstRussianFromPos(const wchar_t* str, int pos);


int geometricMeanOddLowercase(const wchar_t* str);

int lengthFirstWordEndingWithConsonant(const wchar_t* str);

int countOfWordsWithRussianLetter(const wchar_t* str);


void runTests();
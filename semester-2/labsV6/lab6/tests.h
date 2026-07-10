#pragma once

/**
 * @brief Checks if two arrays are equal (same size and elements).
 */
bool arraysEqual(const int* a, int sizeA, const int* b, int sizeB);

// Базовый случай: чётные → квадраты (лямбды inline)
void testEvenSquare();

// Пустой массив
void testEmptyArray();

// Нет подходящих элементов
void testNoMatchingElements();

// Все элементы подходят
void testAllMatch();

// Отрицательные значения (квадрат даёт положительные)
void testNegativeValues();

// Единственный подходящий элемент (граничный случай)
void testSingleMatchingElement();

// Другая стратегия: нечётные → модуль (демонстрация замены лямбд)
void testOddAbs();

// Именованные лямбды (переиспользование)
void testNamedLambdas();

// Большой массив: 20 элементов, половина чётных
void testLargeArray();

// Большой массив: все элементы подходят (15 чётных)
void testLargeArrayAllMatch();

// Большой массив: все нечётные (нет подходящих)
void testLargeArrayNoMatch();

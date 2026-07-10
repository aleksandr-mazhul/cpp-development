#pragma once

#include <iosfwd>
#include <vector>

using Path = std::vector<int>;

// Рекурсивный алгоритм: число путей фишки от начала до позиции n (шаг не более k).
[[nodiscard]] long long countPathsRecursive(int n, int k);

// Нерекурсивный алгоритм: то же самое, реализовано циклом (динамическое программирование).
[[nodiscard]] long long countPathsIterative(int n, int k);

// Рекурсивный перебор: все последовательности ходов от 0 до n.
[[nodiscard]] std::vector<Path> findAllPaths(int n, int k);

// Наглядный вывод комбинаций ходов (targetN — длина поля для подсветки суммы).
void printPaths(const std::vector<Path>& paths, std::ostream& out, int targetN = -1);

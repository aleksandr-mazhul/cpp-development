#include "LinearSystem.h"

#include "ConsoleColors.h"
#include "SystemInput.h"

#include <cmath>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

namespace
{
    std::streamoff matrixRowOffset(int n, int rowIndex)
    {
        return static_cast<std::streamoff>(sizeof(int)) + static_cast<std::streamoff>(rowIndex) * n
               * static_cast<std::streamoff>(sizeof(double));
    }

    std::streamoff vectorTermOffset(int index)
    {
        return static_cast<std::streamoff>(sizeof(int))
               + static_cast<std::streamoff>(index) * static_cast<std::streamoff>(sizeof(double));
    }

    bool isValidN(int n)
    {
        return n >= 1 && n <= MAX_N;
    }

    void printIoError(const char* message)
    {
        std::cerr << Color::red << message << Color::reset << '\n';
    }

    void reportError(const char* message, bool quiet)
    {
        if (!quiet)
        {
            printIoError(message);
        }
    }

    const char* unknownSubscript(int index)
    {
        static const char* const SUBS[] = {"₀", "₁", "₂", "₃", "₄", "₅", "₆", "₇", "₈", "₉"};
        if (index >= 0 && index < 10)
        {
            return SUBS[index];
        }
        return "?";
    }

    bool isZero(double value)
    {
        return std::fabs(value) < 1e-9;
    }

    void appendTerm(std::ostream& out, double coeff, int varIndex, bool& first)
    {
        if (isZero(coeff))
        {
            return;
        }

        if (!first && coeff > 0.0)
        {
            out << " + ";
        }
        else if (!first)
        {
            out << " - ";
        }
        else if (coeff < 0.0)
        {
            out << '-';
        }

        const double absCoeff = std::fabs(coeff);
        if (!isZero(absCoeff - 1.0))
        {
            out << std::fixed << std::setprecision(4);
            if (isZero(absCoeff - static_cast<int>(absCoeff)))
            {
                out << static_cast<int>(absCoeff);
            }
            else
            {
                out << absCoeff;
            }
            out << "·";
        }

        out << 'x' << unknownSubscript(varIndex);
        first = false;
    }
}

bool readSize(const char* path, int& n)
{
    std::ifstream in(path, std::ios::binary);
    if (!in)
    {
        return false;
    }

    in.read(reinterpret_cast<char*>(&n), sizeof(n));
    return static_cast<bool>(in);
}

bool readMatrixRow(const char* path, int n, int rowIndex, double* row)
{
    std::ifstream in(path, std::ios::binary);
    if (!in)
    {
        return false;
    }

    in.seekg(matrixRowOffset(n, rowIndex), std::ios::beg);
    in.read(reinterpret_cast<char*>(row), static_cast<std::streamsize>(n * sizeof(double)));
    return static_cast<bool>(in);
}

bool writeMatrixRow(const char* path, int n, int rowIndex, const double* row)
{
    std::fstream file(path, std::ios::binary | std::ios::in | std::ios::out);
    if (!file)
    {
        return false;
    }

    file.seekp(matrixRowOffset(n, rowIndex), std::ios::beg);
    file.write(reinterpret_cast<const char*>(row), static_cast<std::streamsize>(n * sizeof(double)));
    return static_cast<bool>(file);
}

bool readMatrixElement(const char* path, int n, int rowIndex, int colIndex, double& value)
{
    std::ifstream in(path, std::ios::binary);
    if (!in)
    {
        return false;
    }

    const std::streamoff offset = matrixRowOffset(n, rowIndex)
                                  + static_cast<std::streamoff>(colIndex) * sizeof(double);
    in.seekg(offset, std::ios::beg);
    in.read(reinterpret_cast<char*>(&value), sizeof(value));
    return static_cast<bool>(in);
}

bool swapMatrixRows(const char* path, int n, int rowA, int rowB)
{
    if (rowA == rowB)
    {
        return true;
    }

    double row1[MAX_N]{};
    double row2[MAX_N]{};

    if (!readMatrixRow(path, n, rowA, row1) || !readMatrixRow(path, n, rowB, row2))
    {
        return false;
    }

    return writeMatrixRow(path, n, rowA, row2) && writeMatrixRow(path, n, rowB, row1);
}

bool readVectorTerm(const char* path, int n, int index, double& value)
{
    (void)n;
    std::ifstream in(path, std::ios::binary);
    if (!in)
    {
        return false;
    }

    in.seekg(vectorTermOffset(index), std::ios::beg);
    in.read(reinterpret_cast<char*>(&value), sizeof(value));
    return static_cast<bool>(in);
}

bool writeVectorTerm(const char* path, int n, int index, double value)
{
    (void)n;
    std::fstream file(path, std::ios::binary | std::ios::in | std::ios::out);
    if (!file)
    {
        return false;
    }

    file.seekp(vectorTermOffset(index), std::ios::beg);
    file.write(reinterpret_cast<const char*>(&value), sizeof(value));
    return static_cast<bool>(file);
}

bool swapVectorTerms(const char* path, int n, int indexA, int indexB)
{
    if (indexA == indexB)
    {
        return true;
    }

    double valueA = 0.0;
    double valueB = 0.0;

    if (!readVectorTerm(path, n, indexA, valueA) || !readVectorTerm(path, n, indexB, valueB))
    {
        return false;
    }

    return writeVectorTerm(path, n, indexA, valueB) && writeVectorTerm(path, n, indexB, valueA);
}

bool writeMatrixBinary(const char* path, int n, const double* matrixRowMajor)
{
    if (!isValidN(n))
    {
        return false;
    }

    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    if (!out)
    {
        return false;
    }

    out.write(reinterpret_cast<const char*>(&n), sizeof(n));
    for (int i = 0; i < n; ++i)
    {
        out.write(reinterpret_cast<const char*>(matrixRowMajor + i * n),
                  static_cast<std::streamsize>(n * sizeof(double)));
    }

    return static_cast<bool>(out);
}

bool writeVectorBinary(const char* path, int n, const double* vector)
{
    if (!isValidN(n))
    {
        return false;
    }

    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    if (!out)
    {
        return false;
    }

    out.write(reinterpret_cast<const char*>(&n), sizeof(n));
    out.write(reinterpret_cast<const char*>(vector), static_cast<std::streamsize>(n * sizeof(double)));
    return static_cast<bool>(out);
}

void createBinaryFiles(const char* matrixPath, const char* vectorPath)
{
    int n = 0;
    std::cout << Color::cyan << "Введите размер системы n (1.." << MAX_N << "): " << Color::reset;
    std::cin >> n;

    if (!isValidN(n))
    {
        printIoError("Ошибка: n вне допустимого диапазона.");
        return;
    }

    double matrix[MAX_N * MAX_N]{};
    double vector[MAX_N]{};

    if (!inputSystemFromKeyboard(n, matrix, vector))
    {
        std::cout << Color::yellow << "Ввод отменён.\n" << Color::reset;
        return;
    }

    if (!writeMatrixBinary(matrixPath, n, matrix) || !writeVectorBinary(vectorPath, n, vector))
    {
        printIoError("Ошибка: не удалось сохранить бинарные файлы.");
        return;
    }

    std::cout << Color::green << "Файлы '" << matrixPath << "' и '" << vectorPath
              << "' созданы.\n" << Color::reset;
}

void viewBinaryFiles(const char* matrixPath, const char* vectorPath)
{
    int nMatrix = 0;
    if (!readSize(matrixPath, nMatrix))
    {
        printIoError("Ошибка: не удалось прочитать файл матрицы.");
        return;
    }

    std::cout << Color::yellow << "\n=== Просмотр матрицы: " << matrixPath << " ===\n"
              << Color::reset;
    std::cout << Color::cyan << "Запись 0 (заголовок): n = " << nMatrix << Color::reset << '\n';

    double row[MAX_N]{};
    for (int i = 0; i < nMatrix; ++i)
    {
        if (!readMatrixRow(matrixPath, nMatrix, i, row))
        {
            printIoError("Ошибка чтения строки матрицы.");
            return;
        }

        std::cout << Color::white << "Запись " << (i + 1) << " (строка " << i << "): ";
        for (int j = 0; j < nMatrix; ++j)
        {
            std::cout << row[j] << (j + 1 < nMatrix ? ' ' : '\n');
        }
    }

    int nVector = 0;
    if (!readSize(vectorPath, nVector))
    {
        printIoError("Ошибка: не удалось прочитать файл вектора.");
        return;
    }

    std::cout << Color::yellow << "\n=== Просмотр вектора: " << vectorPath << " ===\n"
              << Color::reset;
    std::cout << Color::cyan << "Запись 0 (заголовок): n = " << nVector << Color::reset << '\n';

    for (int i = 0; i < nVector; ++i)
    {
        double value = 0.0;
        if (!readVectorTerm(vectorPath, nVector, i, value))
        {
            printIoError("Ошибка чтения свободного члена.");
            return;
        }

        std::cout << Color::white << "Запись " << (i + 1) << " (с.ч.[" << i << "]): " << value
                  << '\n';
    }
}

bool solveSystemGauss(const char* matrixPath, const char* vectorPath, const char* resultPath,
                      double* solutionOut, bool quiet)
{
    int nMatrix = 0;
    int nVector = 0;

    if (!readSize(matrixPath, nMatrix))
    {
        reportError("Ошибка: не удалось прочитать размер матрицы.", quiet);
        return false;
    }

    if (!readSize(vectorPath, nVector))
    {
        reportError("Ошибка: не удалось прочитать размер вектора.", quiet);
        return false;
    }

    if (!isValidN(nMatrix) || !isValidN(nVector))
    {
        reportError("Ошибка: размер системы вне допустимого диапазона.", quiet);
        return false;
    }

    if (nMatrix != nVector)
    {
        reportError("Ошибка: размеры матрицы и вектора не совпадают.", quiet);
        return false;
    }

    const int n = nMatrix;
    double rowA[MAX_N]{};
    double rowB[MAX_N]{};
    double x[MAX_N]{};

    for (int k = 0; k < n; ++k)
    {
        int pivotRow = k;
        double maxAbs = 0.0;

        for (int i = k; i < n; ++i)
        {
            double value = 0.0;
            if (!readMatrixElement(matrixPath, n, i, k, value))
            {
                reportError("Ошибка чтения элемента матрицы.", quiet);
                return false;
            }

            const double absValue = std::fabs(value);
            if (absValue > maxAbs)
            {
                maxAbs = absValue;
                pivotRow = i;
            }
        }

        if (maxAbs < EPS)
        {
            reportError("Ошибка: систему решить нельзя (нулевой главный элемент).", quiet);
            return false;
        }

        if (!swapMatrixRows(matrixPath, n, k, pivotRow)
            || !swapVectorTerms(vectorPath, n, k, pivotRow))
        {
            reportError("Ошибка перестановки строк.", quiet);
            return false;
        }

        if (!readMatrixRow(matrixPath, n, k, rowA))
        {
            reportError("Ошибка чтения опорной строки.", quiet);
            return false;
        }

        double pivotRhs = 0.0;
        if (!readVectorTerm(vectorPath, n, k, pivotRhs))
        {
            reportError("Ошибка чтения опорного свободного члена.", quiet);
            return false;
        }

        for (int i = k + 1; i < n; ++i)
        {
            if (!readMatrixRow(matrixPath, n, i, rowB))
            {
                reportError("Ошибка чтения строки при прямом ходе.", quiet);
                return false;
            }

            const double factor = rowB[k] / rowA[k];
            for (int j = k; j < n; ++j)
            {
                rowB[j] -= factor * rowA[j];
            }

            if (!writeMatrixRow(matrixPath, n, i, rowB))
            {
                reportError("Ошибка записи строки при прямом ходе.", quiet);
                return false;
            }

            double rhsValue = 0.0;
            if (!readVectorTerm(vectorPath, n, i, rhsValue))
            {
                reportError("Ошибка чтения свободного члена при прямом ходе.", quiet);
                return false;
            }

            rhsValue -= factor * pivotRhs;
            if (!writeVectorTerm(vectorPath, n, i, rhsValue))
            {
                reportError("Ошибка записи свободного члена при прямом ходе.", quiet);
                return false;
            }
        }
    }

    for (int i = n - 1; i >= 0; --i)
    {
        if (!readMatrixRow(matrixPath, n, i, rowA))
        {
            reportError("Ошибка чтения строки при обратном ходе.", quiet);
            return false;
        }

        double rhsValue = 0.0;
        if (!readVectorTerm(vectorPath, n, i, rhsValue))
        {
            reportError("Ошибка чтения свободного члена при обратном ходе.", quiet);
            return false;
        }

        double sum = rhsValue;
        for (int j = i + 1; j < n; ++j)
        {
            sum -= rowA[j] * x[j];
        }

        if (std::fabs(rowA[i]) < EPS)
        {
            reportError("Ошибка: нулевой диагональный элемент при обратном ходе.", quiet);
            return false;
        }

        x[i] = sum / rowA[i];
    }

    std::ofstream out(resultPath, std::ios::trunc);
    if (!out)
    {
        reportError("Ошибка: не удалось создать файл результата.", quiet);
        return false;
    }

    out << "n = " << n << '\n';
    out << std::fixed << std::setprecision(6);
    for (int i = 0; i < n; ++i)
    {
        out << "x[" << i << "] = " << x[i] << '\n';
    }

    if (solutionOut != nullptr)
    {
        for (int i = 0; i < n; ++i)
        {
            solutionOut[i] = x[i];
        }
    }

    return true;
}

void viewResultFile(const char* path)
{
    std::ifstream in(path);
    if (!in)
    {
        printIoError("Ошибка: не удалось открыть файл результата.");
        return;
    }

    std::cout << Color::yellow << "\n=== Просмотр результата: " << path << " ===\n" << Color::reset;
    std::string line;
    while (std::getline(in, line))
    {
        if (line.rfind("x[", 0) == 0)
        {
            std::cout << Color::green << "  " << line << Color::reset << '\n';
        }
        else if (line.rfind("n =", 0) == 0)
        {
            std::cout << Color::cyan << "  размер: " << line.substr(4) << Color::reset << '\n';
        }
        else
        {
            std::cout << Color::cyan << "  " << line << Color::reset << '\n';
        }
    }
}

void printSystemTable(int n, const double* matrixRowMajor, const double* vector)
{
    std::cout << Color::dim << "      ";
    for (int j = 0; j < n; ++j)
    {
        std::cout << 'x' << unknownSubscript(j) << "    ";
    }
    std::cout << "|  с.ч.\n" << Color::reset;

    for (int i = 0; i < n; ++i)
    {
        std::cout << Color::white << "стр." << (i + 1) << ' ';
        for (int j = 0; j < n; ++j)
        {
            std::cout << std::setw(6) << std::fixed << std::setprecision(1)
                      << matrixRowMajor[i * n + j] << ' ';
        }
        std::cout << Color::cyan << "| " << std::setw(6) << std::setprecision(1) << vector[i]
                  << Color::reset << '\n';
    }
}

void printSystemEquations(int n, const double* matrixRowMajor, const double* vector)
{
    std::cout << Color::yellow << "  Исходное условие:\n" << Color::reset;

    for (int i = 0; i < n; ++i)
    {
        std::cout << Color::white << "  ";
        bool first = true;
        std::ostringstream equation;

        for (int j = 0; j < n; ++j)
        {
            appendTerm(equation, matrixRowMajor[i * n + j], j, first);
        }

        std::string left = equation.str();
        if (left.empty())
        {
            left = "0";
        }

        std::cout << left << Color::cyan << " = " << Color::reset << std::fixed
                  << std::setprecision(4) << vector[i] << '\n';
    }
}

void printSolution(int n, const double* solution)
{
    std::cout << Color::green << "  Решение: ";
    for (int i = 0; i < n; ++i)
    {
        std::cout << 'x' << unknownSubscript(i) << " = " << std::fixed << std::setprecision(6)
                  << solution[i];
        if (i + 1 < n)
        {
            std::cout << ", ";
        }
    }
    std::cout << Color::reset << '\n';
}

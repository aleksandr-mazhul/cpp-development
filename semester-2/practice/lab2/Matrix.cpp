#include "Matrix.h"

#include <cstdlib>
#include <fstream>
#include <iostream>

#if defined(_WIN32)
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace
{
const int CELL_WIDTH = 7;
const int ROW_LABEL_WIDTH = 4;

#if !defined(_WIN32)
termios g_origTermios{};
bool g_rawMode = false;

void enableRawMode()
{
    if (g_rawMode)
        return;

    tcgetattr(STDIN_FILENO, &g_origTermios);
    termios raw = g_origTermios;
    raw.c_lflag &= static_cast<tcflag_t>(~(ICANON | ECHO));
    raw.c_cc[VMIN] = 1;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    g_rawMode = true;
}

void disableRawMode()
{
    if (!g_rawMode)
        return;

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_origTermios);
    g_rawMode = false;
}

int readKey()
{
    char c = 0;

    if (read(STDIN_FILENO, &c, 1) != 1)
        return 0;

    if (c != 27)
        return static_cast<unsigned char>(c);

    char seq[2] = {0, 0};

    if (read(STDIN_FILENO, &seq[0], 1) != 1)
        return 27;

    if (read(STDIN_FILENO, &seq[1], 1) != 1)
        return 27;

    if (seq[0] == '[')
    {
        if (seq[1] == 'A')
            return 1000;
        if (seq[1] == 'B')
            return 1001;
        if (seq[1] == 'C')
            return 1002;
        if (seq[1] == 'D')
            return 1003;
    }

    return 27;
}
#else
void enableRawMode() {}
void disableRawMode() {}

int readKey()
{
    int c = _getch();

    if (c == 224 || c == 0)
    {
        int arrow = _getch();

        if (arrow == 72)
            return 1000;
        if (arrow == 80)
            return 1001;
        if (arrow == 77)
            return 1002;
        if (arrow == 75)
            return 1003;
    }

    return c;
}
#endif

int countDigits(int n)
{
    if (n == 0)
        return 1;

    if (n < 0)
        n = -n;

    int count = 0;

    while (n > 0)
    {
        ++count;
        n /= 10;
    }

    return count;
}

void printLeftGutter(int row)
{
    int spaces = ROW_LABEL_WIDTH;

    if (row >= 0)
    {
        int label = row + 1;
        int digits = countDigits(label);
        spaces = ROW_LABEL_WIDTH - digits;

        while (spaces > 0)
        {
            std::cout << ' ';
            --spaces;
        }

        std::cout << "\033[1;33m" << label << "\033[0m";
        return;
    }

    while (spaces > 0)
    {
        std::cout << ' ';
        --spaces;
    }
}

void printCellSlot(int value, bool active, bool header)
{
    std::cout << "\033[90m|\033[0m ";

    if (header)
        std::cout << "\033[1;33m";
    else if (active)
        std::cout << "\033[48;5;236m\033[38;5;117m\033[1m";
    else
        std::cout << "\033[0m";

    int digits = countDigits(value);
    int pad = CELL_WIDTH - digits;
    int left = pad / 2;
    int right = pad - left;

    while (left > 0)
    {
        std::cout << ' ';
        --left;
    }

    std::cout << value;

    while (right > 0)
    {
        std::cout << ' ';
        --right;
    }

    if (header || active)
        std::cout << "\033[0m";

    std::cout << ' ';
}

int* cellAt(int row, int col)
{
    return *(rowPtrs + row) + col;
}

void commitCell(int row, int col, int value)
{
    *cellAt(row, col) = value;
}

void clearMatrixData()
{
    int** rp = rowPtrs;
    int** rpEnd = rowPtrs + rowCount;

    while (rp < rpEnd)
    {
        int* p = *rp;
        int* pe = *rp + colCount;

        while (p < pe)
        {
            *p = 0;
            ++p;
        }

        ++rp;
    }
}

void drawMatrixGrid(int activeRow, int activeCol, int editValue)
{
    std::cout << "\033[2J\033[H";
    std::cout << "\033[1;36m  Ввод матрицы  \033[0m"
              << "(строк: " << rowCount << ", столбцов: " << colCount << ")\n\n";

    printLeftGutter(-1);
    std::cout << ' ';

    int col = 0;

    while (col < colCount)
    {
        printCellSlot(col + 1, false, true);
        ++col;
    }

    std::cout << "\033[90m|\033[0m\n";

    int row = 0;

    while (row < rowCount)
    {
        printLeftGutter(row);
        std::cout << ' ';

        col = 0;

        while (col < colCount)
        {
            int displayValue = *cellAt(row, col);

            if (row == activeRow && col == activeCol)
                displayValue = editValue;

            printCellSlot(displayValue, row == activeRow && col == activeCol, false);
            ++col;
        }

        std::cout << "\033[90m|\033[0m\n";
        ++row;
    }

    std::cout << "\n\033[1;34mУправление:\033[0m "
              << "стрелки — перемещение | цифры — ввод | Backspace — стереть | "
              << "Enter/Tab — следующая ячейка | Ctrl+S — сохранить | Esc — отмена\n";
}
} // namespace

int data[MAX_ROWS][MAX_COLS];
int* rowPtrs[MAX_ROWS];
int rowCount = 0;
int colCount = 0;

const char* const TESTS_REL_DIR = "tests/";

bool testFileExists(const char* path)
{
    std::ifstream in(path);
    return in.good();
}

void pathAppend(char* out, const char* part)
{
    char* o = out;

    while (*o)
        ++o;

    if (o > out && *(o - 1) != '/')
    {
        *o = '/';
        ++o;
    }

    const char* p = part;

    while (*p)
    {
        *o = *p;
        ++o;
        ++p;
    }

    *o = '\0';
}

void buildLab2TestPath(const char* fileName, char* out)
{
    char* o = out;
    const char* base = LAB2_SOURCE_DIR;
    const char* p = base;

    while (*p)
    {
        *o = *p;
        ++o;
        ++p;
    }

    *o = '\0';
    pathAppend(out, "tests");
    pathAppend(out, fileName);
}

bool buildTestFilePath(const char* fileName, char* out)
{
    char relative[1024];
    char* o = relative;
    const char* p = TESTS_REL_DIR;

    while (*p)
    {
        *o = *p;
        ++o;
        ++p;
    }

    p = fileName;

    while (*p)
    {
        *o = *p;
        ++o;
        ++p;
    }

    *o = '\0';

    if (testFileExists(relative))
    {
        o = out;
        p = relative;

        while (*p)
        {
            *o = *p;
            ++o;
            ++p;
        }

        *o = '\0';

        return true;
    }

    buildLab2TestPath(fileName, out);

    return testFileExists(out);
}

bool parseTwoInts(const char* line, int& first, int& second)
{
    const char* p = line;

    while (*p == ' ' || *p == '\t')
        ++p;

    if (*p == '#' || *p == '\0')
        return false;

    int a = 0;
    int b = 0;
    bool hasA = false;
    bool hasB = false;

    while (*p >= '0' && *p <= '9')
    {
        a = a * 10 + (*p - '0');
        hasA = true;
        ++p;
    }

    while (*p == ' ' || *p == '\t')
        ++p;

    while (*p >= '0' && *p <= '9')
    {
        b = b * 10 + (*p - '0');
        hasB = true;
        ++p;
    }

    if (!hasA || !hasB)
        return false;

    first = a;
    second = b;
    return true;
}

void printTestDescription(const char* path)
{
    std::ifstream in(path);

    if (!in)
        return;

    char line[512];

    while (in.getline(line, 512))
    {
        if (line[0] != '#')
            break;

        std::cout << "\033[0;37m" << line << "\033[0m\n";
    }
}

bool isZeroRow(int rowIndex)
{
    int* p = *(rowPtrs + rowIndex);
    int* end = p + colCount;

    while (p < end)
    {
        if (*p != 0)
            return false;

        ++p;
    }

    return true;
}

bool loadMatrixFromPath(const char* path, bool quiet)
{
    std::ifstream in(path);

    if (!in)
    {
        if (!quiet)
            std::cout << "\033[1;31mОшибка: файл не найден.\033[0m\n";

        return false;
    }

    char line[512];
    bool sizeRead = false;

    while (in.getline(line, 512))
    {
        if (line[0] == '#' || line[0] == '\0')
            continue;

        if (parseTwoInts(line, rowCount, colCount))
        {
            sizeRead = true;
            break;
        }
    }

    if (!sizeRead)
    {
        if (!quiet)
            std::cout << "\033[1;31mОшибка: не удалось прочитать размер матрицы.\033[0m\n";

        return false;
    }

    if (rowCount <= 0 || colCount <= 0 || rowCount > MAX_ROWS || colCount > MAX_COLS)
    {
        if (!quiet)
            std::cout << "\033[1;31mОшибка: некорректный размер матрицы.\033[0m\n";

        return false;
    }

    initRowPtrs();

    int** rp = rowPtrs;
    int** rpEnd = rowPtrs + rowCount;

    while (rp < rpEnd)
    {
        int* p = *rp;
        int* pe = *rp + colCount;

        while (p < pe)
        {
            in >> *p;
            ++p;
        }

        ++rp;
    }

    if (!in)
    {
        if (!quiet)
            std::cout << "\033[1;31mОшибка: не удалось прочитать все элементы.\033[0m\n";

        return false;
    }

    if (!quiet)
        std::cout << "\033[1;32mМатрица загружена из файла.\033[0m\n";

    return true;
}

bool loadMatrixFromFile()
{
    return loadMatrixFromPath(FILE_NAME, false);
}

bool saveMatrixToFile()
{
    std::ofstream out(FILE_NAME);

    if (!out)
    {
        std::cout << "\033[1;31mОшибка: не удалось сохранить matrix.txt.\033[0m\n";
        return false;
    }

    out << rowCount << ' ' << colCount << '\n';

    int** rp = rowPtrs;
    int** rpEnd = rowPtrs + rowCount;

    while (rp < rpEnd)
    {
        int* p = *rp;
        int* pe = *rp + colCount;

        while (p < pe)
        {
            out << *p;

            ++p;

            if (p < pe)
                out << ' ';
        }

        out << '\n';
        ++rp;
    }

    return true;
}

void inputMatrixFromKeyboardAndSave()
{
    std::cout << "Введите число строк и столбцов: ";
    std::cin >> rowCount >> colCount;

    if (rowCount <= 0 || colCount <= 0 || rowCount > MAX_ROWS || colCount > MAX_COLS)
    {
        std::cout << "\033[1;31mОшибка: некорректный размер матрицы.\033[0m\n";
        rowCount = 0;
        colCount = 0;
        return;
    }

    initRowPtrs();
    clearMatrixData();

#if !defined(_WIN32)
    tcflush(STDIN_FILENO, TCIFLUSH);
#endif

    int activeRow = 0;
    int activeCol = 0;
    int editValue = 0;

    enableRawMode();
    drawMatrixGrid(activeRow, activeCol, editValue);

    bool running = true;
    bool saved = false;

    while (running)
    {
        int key = readKey();

        if (key == 3 || key == 19)
        {
            commitCell(activeRow, activeCol, editValue);
            running = false;
            saved = true;
        }
        else if (key == 27)
        {
            running = false;
        }
        else if (key == 1000 && activeRow > 0)
        {
            commitCell(activeRow, activeCol, editValue);
            --activeRow;
            editValue = *cellAt(activeRow, activeCol);
        }
        else if (key == 1001 && activeRow + 1 < rowCount)
        {
            commitCell(activeRow, activeCol, editValue);
            ++activeRow;
            editValue = *cellAt(activeRow, activeCol);
        }
        else if (key == 1002 && activeCol + 1 < colCount)
        {
            commitCell(activeRow, activeCol, editValue);
            ++activeCol;
            editValue = *cellAt(activeRow, activeCol);
        }
        else if (key == 1003 && activeCol > 0)
        {
            commitCell(activeRow, activeCol, editValue);
            --activeCol;
            editValue = *cellAt(activeRow, activeCol);
        }
        else if (key == '\t' || key == '\n' || key == '\r')
        {
            commitCell(activeRow, activeCol, editValue);

            ++activeCol;

            if (activeCol >= colCount)
            {
                activeCol = 0;
                ++activeRow;
            }

            if (activeRow >= rowCount)
            {
                running = false;
                saved = true;
            }
            else
            {
                editValue = *cellAt(activeRow, activeCol);
            }
        }
        else if (key == 127 || key == 8)
        {
            editValue /= 10;
            commitCell(activeRow, activeCol, editValue);
        }
        else if (key >= '0' && key <= '9')
        {
            int digit = key - '0';

            if (editValue <= 214748364)
            {
                editValue = editValue * 10 + digit;
                commitCell(activeRow, activeCol, editValue);
            }
        }

        if (running)
            drawMatrixGrid(activeRow, activeCol, editValue);
    }

    disableRawMode();

    std::cout << "\033[2J\033[H";

    if (saved && saveMatrixToFile())
        std::cout << "\033[1;32mМатрица сохранена в matrix.txt.\033[0m\n";
    else if (!saved)
        std::cout << "\033[1;33mВвод отменён.\033[0m\n";
}

void initRowPtrs()
{
    int* base = data[0];
    int** rp = rowPtrs;
    int** end = rowPtrs + rowCount;

    while (rp < end)
    {
        *rp = base;
        base += MAX_COLS;
        ++rp;
    }
}

void printMatrix(int highlightRow, int newRow)
{
    int** rp = rowPtrs;
    int** end = rowPtrs + rowCount;

    while (rp < end)
    {
        int rowNum = static_cast<int>(rp - rowPtrs);

        if (rowNum == newRow)
            std::cout << "\033[1;32m";
        else if (rowNum == highlightRow)
            std::cout << "\033[1;35m";
        else
            std::cout << "\033[0m";

        int* p = *rp;
        int* pe = *rp + colCount;

        while (p < pe)
        {
            std::cout << *p;

            ++p;

            if (p < pe)
                std::cout << ' ';
        }

        std::cout << "\033[0m\n";
        ++rp;
    }
}

int minDigit(int n)
{
    if (n < 0)
        n = -n;

    if (n == 0)
        return 0;

    int minD = 9;

    while (n > 0)
    {
        int d = n % 10;

        if (d < minD)
            minD = d;

        n /= 10;
    }

    return minD;
}

bool isDescending(int* row, int cols)
{
    if (cols <= 1)
        return true;

    int* p = row;
    int* end = row + cols - 1;

    while (p < end)
    {
        if (*p < *(p + 1))
            return false;

        ++p;
    }

    return true;
}

int countEvenMinDigit(int* row, int cols)
{
    int count = 0;
    int* p = row;
    int* end = row + cols;

    while (p < end)
    {
        if (minDigit(*p) % 2 == 0)
            ++count;

        ++p;
    }

    return count;
}

int** findTargetRow(int& outCount)
{
    outCount = 0;
    int** target = nullptr;

    int** rp = rowPtrs;
    int** end = rowPtrs + rowCount;

    while (rp < end)
    {
        if (isDescending(*rp, colCount))
        {
            int cnt = countEvenMinDigit(*rp, colCount);

            if (cnt > 0 && cnt >= outCount)
            {
                outCount = cnt;
                target = rp;
            }
        }

        ++rp;
    }

    if (target == nullptr)
        outCount = 0;

    return target;
}

namespace
{
const int T_CELL_W = 7;
const int T_ROW_LABEL_W = 4;

enum TestRowKind
{
    TRK_BEFORE_NORMAL,
    TRK_BEFORE_CANDIDATE,
    TRK_BEFORE_WINNER,
    TRK_AFTER_ANCHOR,
    TRK_AFTER_ZERO,
    TRK_AFTER_SHIFTED,
    TRK_AFTER_NORMAL
};

int testCountDigits(int n)
{
    if (n == 0)
        return 1;

    if (n < 0)
        n = -n;

    int count = 0;

    while (n > 0)
    {
        ++count;
        n /= 10;
    }

    return count;
}

void testPrintLeftGutter(int row)
{
    int spaces = T_ROW_LABEL_W;

    if (row >= 0)
    {
        int label = row + 1;
        int digits = testCountDigits(label);
        spaces = T_ROW_LABEL_W - digits;

        while (spaces > 0)
        {
            std::cout << ' ';
            --spaces;
        }

        std::cout << "\033[1;33m" << label << "\033[0m";
        return;
    }

    while (spaces > 0)
    {
        std::cout << ' ';
        --spaces;
    }
}

void testPrintCell(int value, TestRowKind kind)
{
    std::cout << "\033[90m|\033[0m ";

    switch (kind)
    {
    case TRK_BEFORE_NORMAL:
        std::cout << "\033[90m";
        break;
    case TRK_BEFORE_CANDIDATE:
        std::cout << "\033[1;36m";
        break;
    case TRK_BEFORE_WINNER:
        std::cout << "\033[1;35m";
        break;
    case TRK_AFTER_ANCHOR:
        std::cout << "\033[1;35m";
        break;
    case TRK_AFTER_ZERO:
        std::cout << "\033[1;32m";
        break;
    case TRK_AFTER_SHIFTED:
        std::cout << "\033[33m";
        break;
    default:
        std::cout << "\033[0m";
        break;
    }

    int digits = testCountDigits(value);
    int pad = T_CELL_W - digits;
    int left = pad / 2;
    int right = pad - left;

    while (left > 0)
    {
        std::cout << ' ';
        --left;
    }

    std::cout << value;

    while (right > 0)
    {
        std::cout << ' ';
        --right;
    }

    std::cout << "\033[0m ";
}

void printTestGridHeader()
{
    testPrintLeftGutter(-1);
    std::cout << ' ';

    int col = 0;

    while (col < colCount)
    {
        int value = col + 1;
        std::cout << "\033[90m|\033[0m ";
        std::cout << "\033[1;33m";

        int digits = testCountDigits(value);
        int pad = T_CELL_W - digits;
        int left = pad / 2;
        int right = pad - left;

        while (left > 0)
        {
            std::cout << ' ';
            --left;
        }

        std::cout << value;

        while (right > 0)
        {
            std::cout << ' ';
            --right;
        }

        std::cout << "\033[0m ";
        ++col;
    }

    std::cout << "\033[90m|\033[0m\n";
}

TestRowKind beforeRowKind(int rowNum, int targetRow)
{
    if (!isDescending(*(rowPtrs + rowNum), colCount))
        return TRK_BEFORE_NORMAL;

    if (rowNum == targetRow)
        return TRK_BEFORE_WINNER;

    return TRK_BEFORE_CANDIDATE;
}

TestRowKind afterRowKind(int rowNum, int targetRow, int insertRow)
{
    if (insertRow >= 0 && rowNum == insertRow)
        return TRK_AFTER_ZERO;

    if (targetRow >= 0 && rowNum == targetRow)
        return TRK_AFTER_ANCHOR;

    if (insertRow >= 0 && rowNum > insertRow)
        return TRK_AFTER_SHIFTED;

    return TRK_AFTER_NORMAL;
}

void printRowSideNote(TestRowKind kind, int rowNum, int targetRow)
{
    if (kind == TRK_BEFORE_NORMAL)
    {
        std::cout << "  \033[90mне убывает\033[0m";
        return;
    }

    if (kind == TRK_BEFORE_CANDIDATE || kind == TRK_BEFORE_WINNER)
    {
        int cnt = countEvenMinDigit(*(rowPtrs + rowNum), colCount);
        std::cout << "  \033[0;36mcount=" << cnt << "\033[0m";

        if (kind == TRK_BEFORE_CANDIDATE)
            std::cout << "  \033[36mучаствует в выборе\033[0m";
        else
            std::cout << "  \033[1;35mвыбрана — вставка после неё\033[0m";

        return;
    }

    if (kind == TRK_AFTER_ANCHOR)
        std::cout << "  \033[1;35mпосле этой строки вставлена нулевая\033[0m";
    else if (kind == TRK_AFTER_ZERO)
        std::cout << "  \033[1;32mновая нулевая строка\033[0m";
    else if (kind == TRK_AFTER_SHIFTED)
        std::cout << "  \033[33mсдвинута вниз\033[0m";
}
} // namespace

void printTestLegends()
{
    std::cout << "\033[0;36m  До вставки:\033[0m "
              << "\033[1;36mголубой\033[0m — убывающая строка  |  "
              << "\033[1;35mфиолетовый\033[0m — выбранная  |  "
              << "\033[90mсерый\033[0m — не убывает\n";
    std::cout << "\033[0;36m  После вставки:\033[0m "
              << "\033[1;35mфиолетовый\033[0m — строка-якорь  |  "
              << "\033[1;32mзелёный\033[0m — нулевая строка  |  "
              << "\033[33mжёлтый\033[0m — сдвиг вниз\n";
}

void printMatrixBeforeInsert(int targetRow)
{
    printTestGridHeader();

    int row = 0;

    while (row < rowCount)
    {
        TestRowKind kind = beforeRowKind(row, targetRow);

        testPrintLeftGutter(row);
        std::cout << ' ';

        int col = 0;

        while (col < colCount)
        {
            testPrintCell(*(*(rowPtrs + row) + col), kind);
            ++col;
        }

        std::cout << "\033[90m|\033[0m";
        printRowSideNote(kind, row, targetRow);
        std::cout << '\n';

        if (row == targetRow)
        {
            std::cout << "      \033[1;36m--- здесь появится нулевая строка ---\033[0m\n";
        }

        ++row;
    }
}

void printMatrixAfterInsert(int targetRow, int insertRow)
{
    printTestGridHeader();

    int row = 0;

    while (row < rowCount)
    {
        TestRowKind kind = afterRowKind(row, targetRow, insertRow);

        testPrintLeftGutter(row);
        std::cout << ' ';

        int col = 0;

        while (col < colCount)
        {
            testPrintCell(*(*(rowPtrs + row) + col), kind);
            ++col;
        }

        std::cout << "\033[90m|\033[0m";
        printRowSideNote(kind, row, targetRow);
        std::cout << '\n';
        ++row;
    }
}

void printMatrixNoChange(int targetRow)
{
    printTestGridHeader();

    int row = 0;

    while (row < rowCount)
    {
        TestRowKind kind = beforeRowKind(row, targetRow);

        testPrintLeftGutter(row);
        std::cout << ' ';

        int col = 0;

        while (col < colCount)
        {
            testPrintCell(*(*(rowPtrs + row) + col), kind);
            ++col;
        }

        std::cout << "\033[90m|\033[0m";
        printRowSideNote(kind, row, targetRow);
        std::cout << '\n';
        ++row;
    }
}

void printTestAnalysis(int** target, int maxCnt)
{
    if (target == nullptr)
    {
        std::cout << "\033[1;33m\nИтог анализа: подходящая строка не найдена "
                     "(нет убывающих с count > 0).\033[0m\n";
        return;
    }

    int rowNum = static_cast<int>(target - rowPtrs) + 1;
    std::cout << "\033[1;32m\nИтог анализа: строка " << rowNum
              << " — последняя убывающая с максимальным count = " << maxCnt << ".\033[0m\n";
}

bool insertZeroRowAfter(int** afterRow)
{
    if (rowCount >= MAX_ROWS)
        return false;

    int* p = data[rowCount];
    int* end = p + colCount;

    while (p < end)
    {
        *p = 0;
        ++p;
    }

    int** dest = rowPtrs + rowCount;
    int** src = rowPtrs + rowCount - 1;
    int** stop = afterRow;

    while (src > stop)
    {
        *dest = *src;
        --dest;
        --src;
    }

    *(afterRow + 1) = data[rowCount];
    ++rowCount;

    return true;
}

void insertZeroRowTask()
{
    if (rowCount <= 0 || colCount <= 0)
    {
        std::cout << "\033[1;31mОшибка: матрица не загружена. Сначала выберите пункт 1 или 2.\033[0m\n";
        return;
    }

    std::cout << "\033[1;34m\nМатрица ДО обработки:\033[0m\n";
    printTestLegends();
    std::cout << '\n';

    int maxCnt = 0;
    int** target = findTargetRow(maxCnt);

    if (target == nullptr)
    {
        printMatrixNoChange(-1);
        std::cout << "\033[1;33mПодходящая строка не найдена.\033[0m\n";
        return;
    }

    int targetRow = static_cast<int>(target - rowPtrs);
    printMatrixBeforeInsert(targetRow);
    printTestAnalysis(target, maxCnt);

    if (!insertZeroRowAfter(target))
    {
        std::cout << "\033[1;31mОшибка: достигнут максимальный размер матрицы, вставка невозможна.\033[0m\n";
        return;
    }

    std::cout << "\033[1;34m\nМатрица ПОСЛЕ вставки:\033[0m\n";
    printMatrixAfterInsert(targetRow, targetRow + 1);
}

void runAllTests()
{
    struct TestCase
    {
        const char* fileName;
        const char* title;
        int mode;
        int zeroRowIndex;
        const char* purpose;
    };

    const TestCase tests[] = {
        {"01_odna_podhodyashaya.txt", "Одна подходящая строка", 1, 1,
         "Базовый случай: одна убывающая строка с count > 0 — вставка сразу после неё."},
        {"02_poslednyaya_iz_ravnyh.txt", "Последняя при равном count", 1, 4,
         "При равном максимальном count выбирается последняя убывающая строка."},
        {"03_net_ubyvayushih.txt", "Нет убывающих строк", 0, -1,
         "Если ни одна строка не убывает — вставка не выполняется."},
        {"04_net_podhodyashih.txt", "Убывают, но count = 0", 0, -1,
         "Убывающие строки есть, но нет элементов с чётной мин. цифрой — вставки нет."},
    };

    const int testCount = static_cast<int>(sizeof(tests) / sizeof(tests[0]));
    int passed = 0;
    char testPath[1024];

    std::cout << "\033[1;33m\n========== Запуск тестов: " << testCount << " шт. ==========\033[0m\n";
    printTestLegends();
    std::cout << '\n';

    int i = 0;

    while (i < testCount)
    {
        const TestCase& test = tests[i];

        if (!buildTestFilePath(test.fileName, testPath))
        {
            std::cout << "\033[1;31m\n[" << (i + 1) << "/" << testCount
                      << "] ПРОВАЛ — файл не найден: " << test.fileName << "\033[0m\n";
            ++i;
            continue;
        }

        std::cout << "\033[1;36m\n────── Тест " << (i + 1) << "/" << testCount << ": "
                  << test.title << " ──────\033[0m\n";
        printTestDescription(testPath);

        if (!loadMatrixFromPath(testPath, true))
        {
            std::cout << "\033[1;31m\nРезультат: ПРОВАЛ (файл не найден)\033[0m\n";
            ++i;
            continue;
        }

        int rowsBefore = rowCount;
        int maxCnt = 0;
        int** target = findTargetRow(maxCnt);
        int targetRow = (target == nullptr) ? -1 : static_cast<int>(target - rowPtrs);

        std::cout << "\033[1;34m\n--- Исходная матрица ---\033[0m\n";

        if (targetRow >= 0)
            printMatrixBeforeInsert(targetRow);
        else
            printMatrixNoChange(-1);

        printTestAnalysis(target, maxCnt);

        bool ok = false;
        int insertRow = -1;

        if (test.mode == 0)
        {
            ok = (target == nullptr && rowsBefore == rowCount);
            std::cout << "\033[1;34m\n--- Матрица после обработки ---\033[0m\n";
            std::cout << "\033[0;37m(вставка не выполнялась — матрица не изменилась)\033[0m\n\n";
            printMatrixNoChange(targetRow);
        }
        else if (test.mode == 1)
        {
            if (target != nullptr && insertZeroRowAfter(target))
            {
                insertRow = targetRow + 1;
                ok = (rowCount == rowsBefore + 1)
                     && (test.zeroRowIndex >= 0)
                     && isZeroRow(test.zeroRowIndex);

                std::cout << "\033[1;34m\n--- Матрица после вставки ---\033[0m\n";
                printMatrixAfterInsert(targetRow, insertRow);
            }
        }

        if (ok)
            std::cout << "\033[1;32m\n[" << (i + 1) << "/" << testCount << "] ПРОЙДЕН\033[0m\n";
        else
            std::cout << "\033[1;31m\n[" << (i + 1) << "/" << testCount << "] ПРОВАЛ\033[0m\n";

        std::cout << "\033[0;37m  → " << test.purpose << "\033[0m\n";

        if (ok)
            ++passed;

        ++i;
    }

    std::cout << "\033[1;33m\n========== Итог: " << passed << " / " << testCount
              << " тестов пройдено ==========\033[0m\n" << std::flush;
}

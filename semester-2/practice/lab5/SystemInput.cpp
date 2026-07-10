#include "SystemInput.h"

#include "ConsoleColors.h"
#include "LinearSystem.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

#if defined(_WIN32)
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace
{
constexpr int CELL_WIDTH = 8;
constexpr int ROW_LABEL_WIDTH = 4;
constexpr int EDIT_BUF_SIZE = 32;

const char* unknownSubscript(int index)
{
    static const char* const SUBS[] = {"₀", "₁", "₂", "₃", "₄", "₅", "₆", "₇", "₈", "₉"};
    if (index >= 0 && index < 10)
    {
        return SUBS[index];
    }
    return "?";
}

#if !defined(_WIN32)
termios g_origTermios{};
bool g_rawMode = false;

void enableRawMode()
{
    if (g_rawMode)
    {
        return;
    }

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
    {
        return;
    }

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_origTermios);
    g_rawMode = false;
}

int readKey()
{
    char c = 0;
    if (read(STDIN_FILENO, &c, 1) != 1)
    {
        return 0;
    }

    if (c != 27)
    {
        return static_cast<unsigned char>(c);
    }

    char seq[2] = {0, 0};
    if (read(STDIN_FILENO, &seq[0], 1) != 1)
    {
        return 27;
    }
    if (read(STDIN_FILENO, &seq[1], 1) != 1)
    {
        return 27;
    }

    if (seq[0] == '[')
    {
        if (seq[1] == 'A')
        {
            return 1000;
        }
        if (seq[1] == 'B')
        {
            return 1001;
        }
        if (seq[1] == 'C')
        {
            return 1002;
        }
        if (seq[1] == 'D')
        {
            return 1003;
        }
    }

    return 27;
}
#else
void enableRawMode() {}

void disableRawMode() {}

int readKey()
{
    const int c = _getch();
    if (c == 224 || c == 0)
    {
        const int arrow = _getch();
        if (arrow == 72)
        {
            return 1000;
        }
        if (arrow == 80)
        {
            return 1001;
        }
        if (arrow == 77)
        {
            return 1002;
        }
        if (arrow == 75)
        {
            return 1003;
        }
    }
    return c;
}
#endif

void printLeftGutter(int row)
{
    if (row < 0)
    {
        for (int i = 0; i < ROW_LABEL_WIDTH; ++i)
        {
            std::cout << ' ';
        }
        return;
    }

    const int label = row + 1;
    const int digits = label < 10 ? 1 : (label < 100 ? 2 : 3);
    for (int i = 0; i < ROW_LABEL_WIDTH - digits; ++i)
    {
        std::cout << ' ';
    }
    std::cout << Color::yellow << label << Color::reset;
}

void formatCellText(const char* text, char* out, int width)
{
    const int len = static_cast<int>(std::strlen(text));
    const int pad = width - len;
    const int left = pad > 0 ? pad / 2 : 0;
    const int right = pad > 0 ? pad - left : 0;

    int pos = 0;
    for (int i = 0; i < left; ++i)
    {
        out[pos++] = ' ';
    }
    for (int i = 0; i < len && pos < width; ++i)
    {
        out[pos++] = text[i];
    }
    while (pos < width)
    {
        out[pos++] = ' ';
    }
    out[width] = '\0';
}

void printCellSlot(const char* text, bool active, bool header, bool rhsColumn)
{
    std::cout << Color::dim << "|" << Color::reset << ' ';

    if (header)
    {
        std::cout << (rhsColumn ? Color::cyan : Color::yellow);
    }
    else if (active)
    {
        std::cout << "\033[48;5;236m\033[38;5;117m\033[1m";
    }

    char padded[CELL_WIDTH + 1]{};
    formatCellText(text, padded, CELL_WIDTH);
    std::cout << padded;

    if (header || active)
    {
        std::cout << Color::reset;
    }

    std::cout << ' ';
}

void doubleToEditString(double value, char* out, int outSize)
{
    if (std::fabs(value) < 1e-12)
    {
        std::snprintf(out, outSize, "0");
        return;
    }

    std::snprintf(out, outSize, "%.4g", value);
}

double parseEditString(const char* text)
{
    if (text == nullptr || text[0] == '\0')
    {
        return 0.0;
    }
    return std::strtod(text, nullptr);
}

double cellValue(int n, const double* matrixRowMajor, const double* vector, int row, int col)
{
    if (col < n)
    {
        return matrixRowMajor[row * n + col];
    }
    return vector[row];
}

void setCellValue(int n, double* matrixRowMajor, double* vector, int row, int col, double value)
{
    if (col < n)
    {
        matrixRowMajor[row * n + col] = value;
    }
    else
    {
        vector[row] = value;
    }
}

void drawSystemGrid(int n, const double* matrixRowMajor, const double* vector, int activeRow,
                    int activeCol, const char* editBuf, const char* title)
{
    std::cout << "\033[2J\033[H";
    std::cout << Color::cyan << "  " << title << Color::reset << Color::dim << "  (n = " << n
              << ")\n\n" << Color::reset;

    printLeftGutter(-1);
    std::cout << ' ';
    for (int col = 0; col < n; ++col)
    {
        char header[16]{};
        std::snprintf(header, sizeof(header), "x%s", unknownSubscript(col));
        printCellSlot(header, false, true, false);
    }
    printCellSlot("с.ч.", false, true, true);
    std::cout << Color::dim << "|" << Color::reset << '\n';

    for (int row = 0; row < n; ++row)
    {
        printLeftGutter(row);
        std::cout << ' ';

        for (int col = 0; col <= n; ++col)
        {
            char text[EDIT_BUF_SIZE]{};
            if (row == activeRow && col == activeCol)
            {
                std::snprintf(text, sizeof(text), "%s", editBuf);
            }
            else
            {
                doubleToEditString(cellValue(n, matrixRowMajor, vector, row, col), text,
                                   sizeof(text));
            }

            printCellSlot(text, row == activeRow && col == activeCol, false, col == n);
        }

        std::cout << Color::dim << "|" << Color::reset << '\n';
    }

    std::cout << "\n" << Color::blue << "Управление:" << Color::reset << Color::dim
              << " стрелки — перемещение | цифры, '.', '-' — ввод | Backspace — стереть | "
                 "Enter/Tab — следующая ячейка | Ctrl+S — сохранить | Esc — отмена\n"
              << Color::reset;
}

bool runGridEditor(int n, double* matrixRowMajor, double* vector)
{
    int activeRow = 0;
    int activeCol = 0;
    char editBuf[EDIT_BUF_SIZE]{};
    doubleToEditString(cellValue(n, matrixRowMajor, vector, activeRow, activeCol), editBuf,
                       sizeof(editBuf));

#if !defined(_WIN32)
    tcflush(STDIN_FILENO, TCIFLUSH);
#endif

    enableRawMode();

    bool running = true;
    bool saved = false;

    while (running)
    {
        drawSystemGrid(n, matrixRowMajor, vector, activeRow, activeCol, editBuf,
                       "Ввод системы уравнений");

        const int key = readKey();
        const int maxCol = n;
        const int maxRow = n - 1;

        auto commitActive = [&]() {
            setCellValue(n, matrixRowMajor, vector, activeRow, activeCol,
                         parseEditString(editBuf));
        };

        auto loadActive = [&]() {
            doubleToEditString(cellValue(n, matrixRowMajor, vector, activeRow, activeCol), editBuf,
                               sizeof(editBuf));
        };

        if (key == 3 || key == 19)
        {
            commitActive();
            running = false;
            saved = true;
        }
        else if (key == 27)
        {
            running = false;
        }
        else if (key == 1000 && activeRow > 0)
        {
            commitActive();
            --activeRow;
            loadActive();
        }
        else if (key == 1001 && activeRow < maxRow)
        {
            commitActive();
            ++activeRow;
            loadActive();
        }
        else if (key == 1002 && activeCol < maxCol)
        {
            commitActive();
            ++activeCol;
            loadActive();
        }
        else if (key == 1003 && activeCol > 0)
        {
            commitActive();
            --activeCol;
            loadActive();
        }
        else if (key == '\t' || key == '\n' || key == '\r')
        {
            commitActive();
            ++activeCol;
            if (activeCol > maxCol)
            {
                activeCol = 0;
                ++activeRow;
            }

            if (activeRow > maxRow)
            {
                running = false;
                saved = true;
            }
            else
            {
                loadActive();
            }
        }
        else if (key == 127 || key == 8)
        {
            const int len = static_cast<int>(std::strlen(editBuf));
            if (len > 0)
            {
                editBuf[len - 1] = '\0';
                commitActive();
            }
        }
        else if ((key >= '0' && key <= '9') || key == '.' || key == '-')
        {
            const int len = static_cast<int>(std::strlen(editBuf));
            if (len + 1 < EDIT_BUF_SIZE)
            {
                editBuf[len] = static_cast<char>(key);
                editBuf[len + 1] = '\0';
                commitActive();
            }
        }
    }

    disableRawMode();
    std::cout << "\033[2J\033[H";
    return saved;
}
} // namespace

bool inputSystemFromKeyboard(int n, double* matrixRowMajor, double* vector)
{
    if (n < 1 || n > MAX_N)
    {
        return false;
    }

    for (int i = 0; i < n * n; ++i)
    {
        matrixRowMajor[i] = 0.0;
    }
    for (int i = 0; i < n; ++i)
    {
        vector[i] = 0.0;
    }

    return runGridEditor(n, matrixRowMajor, vector);
}

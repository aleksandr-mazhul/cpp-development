#pragma once

#include <ostream>
#include <iostream>
#include <vector>

class Board
{
public:
    Board(int boardSize) : size(boardSize)
    {
        if (size % 2 == 0)
        {
            throw std::invalid_argument("Board size must be odd number (3, 5, 7, ...)");
        }
        reset();
    }

    void reset()
    {
        grid.resize(size);
        for (int i = 0; i < size; i++)
        {
            grid[i].resize(size);
            for (int j = 0; j < size; j++)
            {
                grid[i][j] = ' ';
            }
        }
    }

    bool isInside(int row, int col) const
    {
        return row >= 0 && row < size && col >= 0 && col < size;
    }

    bool isCellEmpty(int row, int col) const
    {
        return grid[row][col] == ' ';
    }

    int getSize() const
    {
        return size;
    }

    bool placeMark(int row, int col, char mark)
    {
        if (!isInside(row, col)) return false;
        if (!isCellEmpty(row, col)) return false;
        grid[row][col] = mark;
        return true;
    }

    bool hasWinner(char mark) const
    {
        for (int row = 0; row < size; row++)
        {
            bool win = true;
            for (int col = 0; col < size; col++)
            {
                if (grid[row][col] != mark)
                {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }

        for (int col = 0; col < size; col++)
        {
            bool win = true;
            for (int row = 0; row < size; row++)
            {
                if (grid[row][col] != mark)
                {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }

        bool win = true;
        for (int i = 0; i < size; i++)
        {
            if (grid[i][i] != mark)
            {
                win = false;
                break;
            }
        }
        if (win) return true;

        win = true;
        for (int i = 0; i < size; i++)
        {
            if (grid[i][size - 1 - i] != mark)
            {
                win = false;
                break;
            }
        }
        if (win) return true;

        return false;
    }

    bool isFull() const
    {
        for (const auto& row : grid)
        {
            for (char cell : row)
            {
                if (cell == ' ') return false;
            }
        }
        return true;
    }

    void print(std::ostream& stream) const
    {
        stream << "\n  ";
        for (int col = 0; col < size; col++)
        {
            stream << " " << col + 1 << "  ";
        }
        stream << "\n";

        for (int row = 0; row < size; row++)
        {
            if (row > 0)
            {
                stream << "  ";
                for (int col = 0; col < size; col++)
                {
                    stream << "---+";
                }
                stream << "\b \n";
            }

            stream << row + 1 << " ";
            for (int col = 0; col < size; col++)
            {
                stream << "| " << grid[row][col] << " ";
            }
            stream << "|\n";
        }
        stream << "\n";
    }

private:
    int size;
    std::vector<std::vector<char>> grid;
};

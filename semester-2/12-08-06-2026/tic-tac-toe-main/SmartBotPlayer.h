#pragma once

#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include "Board.h"
#include "Player.h"

class SmartBotPlayer : public Player
{
public:
    SmartBotPlayer(std::string name, char mark)
        : Player(std::move(name), mark)
    {
    }

    std::pair<int, int> readMove(const Board& board) const override
    {
        char myMark = getMark();
        char enemyMark = (myMark == 'X') ? 'O' : 'X';

        int size = board.getSize();

        // 1. Попытка выиграть
        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                if (!board.isCellEmpty(row, col))
                {
                    continue;
                }

                Board copy = board;

                copy.placeMark(row, col, myMark);

                if (copy.hasWinner(myMark))
                {
                    return {row, col};
                }
            }
        }

        // 2. Блокировка противника
        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                if (!board.isCellEmpty(row, col))
                {
                    continue;
                }

                Board copy = board;

                copy.placeMark(row, col, enemyMark);

                if (copy.hasWinner(enemyMark))
                {
                    return {row, col};
                }
            }
        }

        // 3. Взять центр
        int center = size / 2;

        if (board.isCellEmpty(center, center))
        {
            return {center, center};
        }

        // 4. Попробовать углы
        std::vector<std::pair<int, int>> corners =
        {
            {0, 0},
            {0, size - 1},
            {size - 1, 0},
            {size - 1, size - 1}
        };

        for (const auto& [row, col] : corners)
        {
            if (board.isCellEmpty(row, col))
            {
                return {row, col};
            }
        }

        // 5. Любая свободная клетка
        for (int row = 0; row < size; row++)
        {
            for (int col = 0; col < size; col++)
            {
                if (board.isCellEmpty(row, col))
                {
                    return {row, col};
                }
            }
        }

        return {0, 0};
    }
};

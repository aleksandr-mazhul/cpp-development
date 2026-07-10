#pragma once

#include <string>
#include <utility>

#include "Board.h"
#include "Player.h"

class HumanPlayer : public Player
{
public:
    HumanPlayer(std::string name, char mark) : Player(std::move(name), mark)
    {
    }

    std::pair<int, int> readMove(const Board& board) const override
    {
        while (true)
        {
            std::cout << getName() << " enter number of row(1-size) and col(1-size): " << std::endl;
            int row, column;
            std::cin >> row >> column;

            int boardRow = row - 1;
            int boardCol = column - 1;

            if (boardRow >= 0 && boardRow < board.getSize() &&
                boardCol >= 0 && boardCol < board.getSize())
            {
                return {boardRow, boardCol};
            }

            std::cout << "Error! Coordinates outside the board! Use numbers 1 to "
                << board.getSize() << std::endl;
        }
    }
};

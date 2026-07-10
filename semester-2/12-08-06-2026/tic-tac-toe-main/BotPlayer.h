#pragma once

#include <string>
#include <utility>

#include "Board.h"
#include "Player.h"

class BotPlayer : public Player
{
public:
    BotPlayer(std::string name, char mark) : Player(std::move(name), mark)
    {
    }

    std::pair<int, int> readMove(const Board& board) const override
    {
        while (true)
        {
            int randomRow = std::rand() % board.getSize();
            int randomColumn = std::rand() % board.getSize();
            if (board.isCellEmpty(randomRow, randomColumn))
            {
                return {randomRow, randomColumn};
            }
        }
    }
};

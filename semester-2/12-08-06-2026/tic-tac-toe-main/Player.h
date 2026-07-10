#pragma once

#include <iostream>

#include "Board.h"

class Player
{
public:
    Player(std::string name, char mark) : name(std::move(name)), mark(mark)
    {
    }

    virtual ~Player() = default;

    const std::string& getName() const
    {
        return name;
    }

    char getMark() const
    {
        return mark;
    }

    virtual std::pair<int, int> readMove(const Board& board) const = 0;

private:
    std::string name;
    char mark;
};

std::ostream& operator<<(std::ostream& stream, const Player& player)
{
    stream << player.getName() << ":" << player.getMark();
    return stream;
}

#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

#include "Level.h"

class Game
{
public:
    void addLevel(std::unique_ptr<Level> level)
    {
        (void)level;
        throw std::logic_error("Game::addLevel is not implemented");
    }

    std::size_t levelsCount() const
    {
        throw std::logic_error("Game::levelsCount is not implemented");
    }

private:
    std::vector<std::unique_ptr<Level>> levels;
};

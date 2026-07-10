#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

#include "Enemy.h"

class Level
{
public:
    void addEnemy(std::unique_ptr<Enemy> enemy)
    {
        (void)enemy;
        throw std::logic_error("Level::addEnemy is not implemented");
    }

    std::size_t enemiesCount() const
    {
        throw std::logic_error("Level::enemiesCount is not implemented");
    }

private:
    std::vector<std::unique_ptr<Enemy>> enemies;
};

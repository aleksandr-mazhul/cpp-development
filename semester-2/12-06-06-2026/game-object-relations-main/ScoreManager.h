#pragma once

#include <stdexcept>

class ScoreManager
{
public:
    void addPoints(int points)
    {
        (void)points;
        throw std::logic_error("ScoreManager::addPoints is not implemented");
    }

    int getTotalScore() const
    {
        throw std::logic_error("ScoreManager::getTotalScore is not implemented");
    }

private:
    int totalScore = 0;
};

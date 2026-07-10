#pragma once

#include <memory>
#include <stdexcept>

#include "Weapon.h"

class Enemy;
class ScoreManager;

class Player
{
public:
    explicit Player(std::shared_ptr<Weapon> weapon) : weapon(std::move(weapon))
    {
        throw std::logic_error("Player::Player is not implemented");
    }

    void setTarget(Enemy* enemy)
    {
        (void)enemy;
        throw std::logic_error("Player::setTarget is not implemented");
    }

    void rewardKill(ScoreManager& scoreManager, int points) const
    {
        (void)scoreManager;
        (void)points;
        throw std::logic_error("Player::rewardKill is not implemented");
    }

    const Weapon& getWeapon() const
    {
        throw std::logic_error("Player::getWeapon is not implemented");
    }

private:
    std::shared_ptr<Weapon> weapon;
    Enemy* targetEnemy = nullptr;
};

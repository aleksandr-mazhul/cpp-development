#pragma once

#include <memory>
#include <stdexcept>

#include "Weapon.h"

class Player;

class Enemy
{
public:
    Enemy(std::shared_ptr<Weapon> weapon, Player* playerToChase)
        : weapon(std::move(weapon)), playerToChase(playerToChase)
    {
        throw std::logic_error("Enemy::Enemy is not implemented");
    }

    const Weapon& getWeapon() const
    {
        throw std::logic_error("Enemy::getWeapon is not implemented");
    }

private:
    std::shared_ptr<Weapon> weapon;
    Player* playerToChase = nullptr;
};

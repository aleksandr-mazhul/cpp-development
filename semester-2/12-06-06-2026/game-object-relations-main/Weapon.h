#pragma once

#include <stdexcept>
#include <string>

class Weapon
{
public:
    explicit Weapon(std::string name) : name(std::move(name))
    {
        throw std::logic_error("Weapon::Weapon is not implemented");
    }

    const std::string& getName() const
    {
        throw std::logic_error("Weapon::getName is not implemented");
    }

private:
    std::string name;
};

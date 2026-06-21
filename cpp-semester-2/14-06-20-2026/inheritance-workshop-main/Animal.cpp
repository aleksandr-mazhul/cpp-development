#include "Animal.h"

#include <iostream>

Animal::Animal(const std::string& name, int age)
    : name(name)
    , age(age)
{
}

void Animal::eat() const
{
    std::cout << name << " is eating\n";
}

void Animal::sleep() const
{
    std::cout << name << " is sleeping\n";
}

std::string Animal::getName() const
{
    return name;
}

int Animal::getAge() const
{
    return age;
}

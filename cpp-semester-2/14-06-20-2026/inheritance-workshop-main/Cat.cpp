#include "Cat.h"

#include <iostream>

Cat::Cat(const std::string& name,
         int age,
         bool indoor)
    : Animal(name, age)
    , indoor(indoor)
{
}

void Cat::meow() const
{
    std::cout << getName()
              << " says meow\n";
}

void Cat::purr() const
{
    std::cout << getName()
              << " is purring\n";
}

void Cat::status() const
{
    std::cout
        << "Name: " << getName()
        << "\nAge: " << getAge()
        << "\nIndoor: "
        << (indoor ? "yes" : "no")
        << '\n';
}

#include "Dog.h"

#include <iostream>

bool Dog::isTrained() const
{
    return trained;
}

Dog::Dog(const std::string& name, int age, const std::string& breed, bool trained)
    : Animal(name, age)
    , breed(breed)
    , trained(trained)
{
}

void Dog::bark() const
{
    std::cout << getName() << " is barking\n";
}

void Dog::fetch() const
{
    std::cout << getName() << " is fetching a ball\n";
}

void Dog::status() const
{
    std::cout << "Name: " << getName() << "\nAge: " << getAge() << "\nBreed: " << breed
              << "\nTrained: " << (trained ? "yes" : "no") << '\n';
}

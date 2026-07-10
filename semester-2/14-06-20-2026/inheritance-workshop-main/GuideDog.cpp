#include "GuideDog.h"

#include <iostream>

GuideDog::GuideDog(const std::string& name, int age, const std::string& breed, bool trained)
    : Dog(name, age, breed, trained)
{
}

void GuideDog::guide() const
{
    std::cout << getName() << " is guiding the owner\n";
}

void GuideDog::performCommand(const std::string& command)
{
    if (!isTrained())
    {
        std::cout << getName() << " is not trained\n";

        return;
    }

    std::cout << getName() << " (guide dog): ";

    Trainable::performCommand(command);
}

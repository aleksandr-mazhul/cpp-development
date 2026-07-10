#include "Trainable.h"

#include <iostream>

void Trainable::performCommand(const std::string& command)
{
    std::cout << "Executing command: " << command << '\n';
}

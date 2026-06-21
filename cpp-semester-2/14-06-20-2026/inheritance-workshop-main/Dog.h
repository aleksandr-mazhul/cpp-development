#pragma once

#include "Animal.h"
#include <string>

class Dog : public Animal
{
private:
    std::string breed;
    bool trained;

protected:
    bool isTrained() const;

public:
    Dog(const std::string& name,
         int age,
         const std::string& breed,
         bool trained);

    void bark() const;
    void fetch() const;
    void status() const;
};

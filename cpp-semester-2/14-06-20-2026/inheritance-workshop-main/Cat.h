#pragma once
#include <string>

#include "Animal.h"

class Cat :public Animal
{
private:
    bool indoor;

public:
    Cat(const std::string& name, int age, bool indoor);

    void meow() const;
    void purr() const;
    void status() const;
};

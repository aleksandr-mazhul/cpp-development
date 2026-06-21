#pragma once

#include <string>

class Animal
{
private:
    std::string name;
    int age;

public:
    Animal(const std::string& name, int age);

    void eat() const;
    void sleep() const;

    std::string getName() const;
    int getAge() const;
};

#pragma once

#include "Dog.h"
#include "Trainable.h"

class GuideDog : public Dog, public Trainable
{
  public:
    GuideDog(const std::string& name, int age, const std::string& breed, bool trained);

    void guide() const;

    void performCommand(const std::string& command) override;
};

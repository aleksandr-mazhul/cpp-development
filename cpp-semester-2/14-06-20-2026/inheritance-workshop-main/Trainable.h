#pragma once
#include <string>

class Trainable
{
    public:
    virtual ~Trainable() = default;

    virtual void performCommand( const std::string& command);
};

#pragma once

#include <string>

class Product
{
public:
    std::string name;
    long long price;
    int quantity;

    long long getTotalAmount() const
    {
        return price * quantity;
    }
};

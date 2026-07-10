#pragma once
#include "Pizza.h"

#include <string>
#include <vector>
#include <fstream>

class Order
{
public:
    Order(int number, const std::string& name);

    int totalPrice() const;

    void addPizza(const Pizza& pizza);

    int count() const;

    void saveToFile(const std::string& fileName) const;
    friend std::ostream& operator<<(std::ostream& os, const Order& order);

private:
    int orderNumber;
    std::string customerName;
    std::vector<Pizza> pizzas;
};

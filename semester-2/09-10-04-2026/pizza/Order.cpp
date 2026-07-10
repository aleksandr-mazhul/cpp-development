#include "Order.h"

#include "Pizza.h"
#include <fstream>

Order::Order(int number, const std::string& name)
    : orderNumber(number)
      , customerName(name)
{
}

int Order::totalPrice() const
{
    int total = 0;
    for (const auto& pizza : pizzas)
    {
        total += pizza.getPrice();
    }
    return total;
}

void Order::addPizza(const Pizza& pizza)
{
    pizzas.push_back(pizza);
}

int Order::count() const
{
    return pizzas.size();
}

void Order::saveToFile(const std::string& fileName) const
{
    std::ofstream out(fileName);
    if (!out)
    {
        throw std::runtime_error("Could not open file for writing");
    }
    out << *this;
}

std::ostream& operator<<(std::ostream& os, const Order& order)
{
    os << "====== Order #" << order.orderNumber << " ======\n";
    os << "Client: " << order.customerName << "\n\n";

    for (const auto& p : order.pizzas)
    {
        os << p << "\n\n";
    }

    os << "Total: " << order.totalPrice() << "\n";

    return os;
}

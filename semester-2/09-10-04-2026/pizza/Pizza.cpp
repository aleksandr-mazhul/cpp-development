#include "Pizza.h"

int Pizza::getPrice() const
{
    int price = 0;

    if (size == "small")
        price = 300;
    if (size == "medium")
        price = 500;
    if (size == "large")
        price = 700;

    price += toppings.size() * 50;

    return price;
}

Pizza::Builder& Pizza::Builder::setSize(const std::string& size)
{
    pizza.size = size;
    return *this;
}

Pizza::Builder& Pizza::Builder::setDough(const std::string& dough)
{
    pizza.dough = dough;
    return *this;
}

Pizza::Builder& Pizza::Builder::setSauce(const std::string& sauce)
{
    pizza.sauce = sauce;
    return *this;
}

Pizza::Builder& Pizza::Builder::addTopping(const std::string& topping)
{
    pizza.toppings.push_back(topping);
    return *this;
}

Pizza Pizza::Builder::build()
{
    return pizza;
}

std::ostream& operator<<(std::ostream& os, const Pizza& pizza)
{
    os << pizza.size << ", "
       << pizza.dough << ", "
       << pizza.sauce << "\n";

    if (pizza.toppings.empty())
    {
        os << "(no toppings)\n";
    }
    else
    {
        for (size_t i = 0; i < pizza.toppings.size(); ++i)
        {
            os << pizza.toppings[i];

            if (i != pizza.toppings.size() - 1)
            {
                os << ", ";
            }
        }

        os << "\n";
    }

    os << "Price: " << pizza.getPrice();

    return os;
}

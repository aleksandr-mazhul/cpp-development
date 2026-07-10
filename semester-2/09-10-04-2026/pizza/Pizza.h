#pragma once
#include <ostream>
#include <string>
#include <vector>

class Pizza
{
public:
    class Builder;
    friend std::ostream& operator<<(std::ostream& os, const Pizza& pizza);
    [[nodiscard]] int getPrice() const;

private:
    Pizza() = default;
    std::string size{"medium"};
    std::string dough{"thin"};
    std::string sauce{"tomato"};
    std::vector<std::string> toppings;
};

class Pizza::Builder
{
public:
    Builder& setSize(const std::string& size);
    Builder& setDough(const std::string& dough);
    Builder& setSauce(const std::string& sauce);
    Builder& addTopping(const std::string& topping);
    Pizza build();

private:
    Pizza pizza;
};

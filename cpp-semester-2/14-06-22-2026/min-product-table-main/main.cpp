#include "Product.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

std::vector<Product> loadFromCSV(const std::string& fileName);

void createReport(const std::vector<Product>& products, std::ostream& out);

void createJsonReport(const std::vector<Product>& products, std::ostream& out);

void sortByTotalAmount(std::vector<Product>& products)
{
    std::sort(products.begin(),
              products.end(),
              [](const Product& a, const Product& b)
              {
                  return a.getTotalAmount() < b.getTotalAmount();
              });
}

int main()
{
    try
    {
        std::vector<Product> products
            = loadFromCSV("/Users/alexandermazhul/CLionProjects/mazhul-cpp-development/"
                          "cpp-semester-2/14-06-22-2026/min-product-table-main/products.csv");
        sortByTotalAmount(products);

        for (const auto& p : products)
        {
            std::cout << p.name << " " << p.price << " " << p.quantity << "\n";
        }

        std::ofstream textFile("report.txt");
        createReport(products, textFile);
        createReport(products, std::cout);

        std::ofstream jsonFile("report.json");
        createJsonReport(products, std::cout);
        createJsonReport(products, jsonFile);
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << "\n";
    }

    return 0;
}

std::vector<Product> loadFromCSV(const std::string& fileName)
{
    std::ifstream stream(fileName);

    if (!stream)
    {
        throw std::runtime_error("Could not open file: " + fileName);
    }

    std::string header;
    std::getline(stream, header);

    std::vector<Product> products;

    std::string line;

    while (std::getline(stream, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::istringstream lineStream(line);
        std::vector<std::string> cells;

        std::string cell;

        while (std::getline(lineStream, cell, ','))
        {
            cells.push_back(cell);
        }

        if (cells.size() == 3)
        {
            Product product;

            product.name = cells[0];
            product.price = std::stoll(cells[1]);
            product.quantity = std::stoi(cells[2]);

            products.push_back(product);
        }
    }

    return products;
}

void createReport(const std::vector<Product>& products, std::ostream& out)
{
    if (!out)
    {
        throw std::runtime_error("error");
    }
    out << std::left << std::setw(20) << "Name" << std::setw(12) << "Price" << std::setw(12)
        << "Quantity" << std::setw(15) << "Total Amount"
        << "\n";
    out << std::string(59, '-') << "\n";

    for (const auto& p : products)
    {
        out << std::left << std::setw(20) << p.name << std::setw(12) << p.price << std::setw(12)
            << p.quantity << std::setw(15) << p.getTotalAmount() << "\n";
    }
}

void createJsonReport(const std::vector<Product>& products, std::ostream& out)
{
    if (!out)
    {
        throw std::runtime_error("error");
    }

    out << "{\n  \"products\": [\n";
    for (size_t i = 0; i < products.size(); ++i)
    {
        const auto& p = products[i];
        out << "    {\n"
            << "      \"name\": \"" << p.name << "\",\n"
            << "      \"price\": " << p.price << ",\n"
            << "      \"quantity\": " << p.quantity << ",\n"
            << "      \"totalAmount\": " << p.getTotalAmount() << "\n"
            << "    }";
        if (i != products.size() - 1)
        {
            out << ",";
        }
        out << "\n";
    }
    out << "  ]\n}\n";
};

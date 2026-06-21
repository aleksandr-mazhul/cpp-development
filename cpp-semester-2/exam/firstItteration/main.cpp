#include "Employee.h"
#include "EmployeesIO.h"

#include <functional>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <vector>

int main()
{
    try
    {
        std::ifstream fin("/Users/alexandermazhul/clion-projects/mazhul-cpp-development/cpp-semester-2/exam/firstItteration/employees.csv");
        if (!fin)
        {
            throw std::runtime_error("Can't open employees.csv");
        }
        std::vector<Employee> employees = EmployeesIO::readFromCsv(fin);
        EmployeesIO::writeToText(std::cout, employees);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
    }
}

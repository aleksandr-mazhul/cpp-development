#include "Employee.h"
#include "EmployeeFilter.h"
#include "EmployeesIO.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

int main()
{
    try
    {
        std::ifstream fin("/Users/alexandermazhul/projects/archive/cpp-development/semester-2/exam/"
                          "first-iteration/employees.csv");
        if (!fin)
        {
            throw std::runtime_error("Can't open employees.csv");
        }
        std::vector<Employee> employees = EmployeesIO::readFromCsv(fin);
        EmployeesIO::writeToText(std::cout, employees);

        std::ofstream fout("/Users/alexandermazhul/projects/archive/cpp-development/semester-2/"
                           "exam/first-iteration/binary.dat",
                           std::ios::binary);
        if (!fout)
        {
            throw std::runtime_error("Can't open binary file");
        }
        EmployeesIO::writeToBinary(fout, employees);
        fout.close();

        std::ifstream bin("/Users/alexandermazhul/projects/archive/cpp-development/semester-2/exam/"
                          "first-iteration/binary.dat",
                          std::ios::binary);
        if (!bin)
        {
            throw std::runtime_error("Can't open binary.dat");
        }

        std::vector<Employee> loadedEmployees = EmployeesIO::readFromBinary(bin);

        std::cout << "\n=== Loaded from binary ===\n";

        EmployeesIO::writeToText(std::cout, loadedEmployees);

        std::vector<Employee> filteredByExp = filterEmployees(employees,[]( const Employee& employee)
        {
            return employee.getYearsOfExperience() > 10;
        });

        std::cout << "\n=== Filtered Employees ===\n";
        EmployeesIO::writeToText(std::cout,filteredByExp);
    }

    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
    }
}

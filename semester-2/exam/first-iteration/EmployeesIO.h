#pragma once
#include "Employee.h"

#include <istream>
#include <ostream>
#include <vector>

class EmployeesIO
{
  public:
    static std::vector<Employee> readFromCsv(std::istream& in);
    static std::vector<Employee> readFromBinary(std::istream& in);
    static void writeToBinary(std::ostream& out, const std::vector<Employee>& employees);
    static void writeToText(std::ostream& out, const std::vector<Employee>&);

  private:
    static bool readEmployee(std::istream& in, Employee& employee);
    static void writeEmployee(std::ostream& out, const Employee& employee);
    static bool readExact(std::istream& in, char* buffer, std::streamsize size);
    static Employee parseEmployee(const std::string& line);
};

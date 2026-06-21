#pragma once
#include "Employee.h"

class EmployeesIO
{
public:
    static const int MaxEmployees = 5;

    static void writeToBinary(std::ofstream& fout, const Employee* employees, const int count);

    static Employee* readFromBinary(std::ifstream& fin, int& count);

    static void writeToText(std::ostream& out, const Employee* employees, const int count);

};


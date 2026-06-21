#include "Employee.h"

#include <stdexcept>
#include <string>
#include <iostream>

Employee::Employee() = default;

Employee::Employee(const std::string& name, int age, double salary, int yearsOfExperience)
{
    validateName(name);
    validateAge(age);
    this->age = age;
    validateSalary(salary);
    validateYearsOfExperience(yearsOfExperience, age);

    this->name = name;
    this->salary = salary;
    this->yearsOfExperience = yearsOfExperience;
}

const std::string& Employee::getName() const
{
    return name;
}
int Employee::getAge() const
{
    return age;
}
double Employee::getSalary() const
{
    return salary;
}
int Employee::getYearsOfExperience() const
{
    return yearsOfExperience;
}

void Employee::validateName(const std::string& name)
{
    if (name.empty())
    {
        throw std::invalid_argument("Name can't be empty ");
    }
}
void Employee::validateAge(int age)
{
    if (age <= 0)
    {
        throw std::invalid_argument("Age can't be negative");
    }
}
void Employee::validateSalary(double salary)
{
    if (salary < 0)
    {
        throw std::invalid_argument("salary can't be negative");
    }
}
void Employee::validateYearsOfExperience(int yearsOfExperience, int age)
{
    if (yearsOfExperience < 0)
    {
        throw std::invalid_argument("yearsOfExperience can't be negative");
    }
    if (yearsOfExperience > age - 18)
    {
        throw std::invalid_argument("Experience cannot be greater than age - 18");
    }
}



std::ostream& operator<<(std::ostream& out, const Employee& employee)
{
    if (!out)
    {
        throw std::runtime_error("Failed to write text data: stream is not valid");
    }

    out << "Name: " << employee.getName()
        << ", Age: " << employee.getAge()
        << ", Salary: " << employee.getSalary()
        << ", Experience: " << employee.getYearsOfExperience()
        << "\n";

    if (out.fail())
    {
        throw std::runtime_error("Failed to write text data: write operation failed");
    }

    return out;
}

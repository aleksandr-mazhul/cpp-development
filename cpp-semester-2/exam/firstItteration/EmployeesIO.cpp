#include "EmployeesIO.h"

#include <sstream>

std::vector<Employee> EmployeesIO::readFromCsv(std::istream& in)
{
    if (!in)
    {
        throw std::runtime_error("Can't open input file: input stream is not valid");
    }

    std::vector<Employee> employees;

    std::string line;
    std::getline(in, line);
    while (std::getline(in, line))
    {
        employees.push_back(parseEmployee(line));
    }
    return employees;
}

std::vector<Employee> EmployeesIO::readFromBinary(std::istream& in)
{
    if (!in)
    {
        throw std::runtime_error("Failed to read from binary: stream is not valid");
    }

    std::vector<Employee> employees;
    Employee employee;
    while (readEmployee(in, employee))
    {
        employees.push_back(std::move(employee));
    }
    return employees;
}

void EmployeesIO::writeToBinary(std::ostream& out, const std::vector<Employee>& employees)
{
    if (!out)
    {
        throw std::runtime_error("out stream is failed to write binary");
    }
    for (const Employee& employee : employees)
    {
        writeEmployee(out, employee);
    }

}

void EmployeesIO::writeToText(std::ostream& out, const std::vector<Employee>& employees)
{
    if (!out)
    {
        throw std::runtime_error("Failed to write to text: stream is not valid");
    }

    for (const Employee& employee : employees)
    {
        out << employee;
    }

    if (out.fail())
    {
        throw std::runtime_error("Failed to write text data: write operation failed");
    }
}

bool EmployeesIO::readEmployee(std::istream& in, Employee& employee)
{
    std::uint16_t nameLength = 0;
    if (!readExact(in, reinterpret_cast<char*>(&nameLength), sizeof(nameLength)))
    {
        return false;
    }
    if (nameLength == 0 || nameLength >= Employee::NameSize)
    {
        throw std::runtime_error("Invalid name length in binary file");
    }

    std::string name(nameLength, '\0');
    if (!readExact(in, name.data(), nameLength))
    {
        throw std::runtime_error("Unexpected end if binary file while reading name");
    }


    int age = 0;
    double salary = 0.0;
    int yearsOfExperience = 0;

    if (!readExact(in, reinterpret_cast<char*>(&age), sizeof(age))
        || !readExact(in, reinterpret_cast<char*>(&salary), sizeof(salary))
        || !readExact(in, reinterpret_cast<char*>(&yearsOfExperience), sizeof(yearsOfExperience)))
    {
        throw std::runtime_error("Unexpected end of binary file while reading employee fields");
    }

    employee = Employee(name, age, salary, yearsOfExperience);
    return true;
}

void EmployeesIO::writeEmployee(std::ostream& out, const Employee& employee)
{
    const std::string& name = employee.getName();
    const std::uint16_t nameLength = static_cast<std::uint16_t>(name.size());

    out.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
    out.write(name.data(), static_cast<std::streamsize>(nameLength));

    const int age = employee.getAge();
    const double salary = employee.getSalary();
    const int yearsOfExperience = employee.getYearsOfExperience();

    out.write(reinterpret_cast<const char*>(&age), sizeof(age));
    out.write(reinterpret_cast<const char*>(&salary), sizeof(salary));
    out.write(reinterpret_cast<const char*>(&yearsOfExperience), sizeof(yearsOfExperience));

    if (out.fail())
    {
        throw std::runtime_error("Failed to write Employee to binary stream");
    }
}

bool EmployeesIO::readExact(std::istream& in, char* buffer, const std::streamsize size)
{

    if (size == 0)
    {
        return true;
    }

    in.read(buffer, size);
    return in.gcount() == size;
}

Employee EmployeesIO::parseEmployee(const std::string& line)
{
    std::string name;
    std::string ageStr;
    std::string salaryStr;
    std::string expStr;

    std::stringstream ss(line);
    if (!std::getline(ss, name, ',')
        || !std::getline(ss, ageStr, ',')
        || !std::getline(ss, salaryStr, ',')
        || !std::getline(ss, expStr, ','))
    {
        throw std::runtime_error("Invalid CSV row");
    }

    const int age = std::stoi(ageStr);
    const double salary = std::stod(salaryStr);
    const int exp = std::stoi(expStr);

    return Employee(name, age, salary, exp);
}

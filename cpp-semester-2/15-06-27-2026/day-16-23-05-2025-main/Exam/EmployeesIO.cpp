#include "EmployeesIO.h"
#include <stdexcept>

const double HighSalaryThreshold = 1000.0;

void EmployeesIO::writeToBinary(std::ofstream& fout, const Employee* employees, int count)
{
	if (!fout)
	{
		throw std::runtime_error("Failed to write sample data: stream is not valid");
	}

	for (int i = 0; i < count; ++i)
	{
		employees[i].writeBinary(fout);
	}
}

Employee* EmployeesIO::readFromBinary(std::ifstream& fin, int& count)
{
	if (!fin)
	{
		throw std::runtime_error("Failed to read from binary: stream is not valid");
	}

	count = 0;

	Employee* employees{ new Employee[EmployeesIO::MaxEmployees] };

	while (employees[count].readBinary(fin))
	{
		++count;
	}
	return employees;
}

void EmployeesIO::writeToText(std::ostream& out, const Employee* employees, int count)
{
	if (!out)
	{
		throw std::runtime_error("Failed to write to text: stream is not valid");
	}
	if (!employees)
	{
		throw std::invalid_argument("Employees array cannot be null");
	}
	if (count < 0)
	{
		throw std::invalid_argument("Count cannot be negative");
	}

	for (int i = 0; i < count; ++i)
	{
		employees[i].writeText(out);
	}
}

#define _CRT_SECURE_NO_DEPRECATE

#include "Employee.h"

Employee::Employee()
{
	std::memset(name, 0, sizeof(name));
	age = 0;
	salary = 0.0;
	yearsOfExperience = 0;
}

Employee::Employee(const char* n, int a, double s, int y)
{
	validateName(n);
	validateAge(a);
	age = a;
	validateSalary(s);
	validateExperience(y);

	std::strncpy(name, n, sizeof(name) - 1);
	name[sizeof(name) - 1] = '\0';	
	salary = s;
	yearsOfExperience = y;
}

const char* Employee::getName() const { return name; }
int Employee::getAge() const { return age; }
double Employee::getSalary() const { return salary; }
int Employee::getExperience() const { return yearsOfExperience; }

void Employee::writeBinary(std::ofstream& fout) const
{
	if (!fout)
	{
		throw std::runtime_error("Failed to write binary data: stream is not valid");
	}
	fout.write((const char*)(this), sizeof(Employee));

	if (!fout)
	{
		throw std::runtime_error("Failed to write binary data: write operation failed");
	}
}

bool Employee::readBinary(std::ifstream& fin)
{
	if (!fin)
	{
		throw std::runtime_error("Failed to read binary data: stream is not valid");
	}
	fin.read(reinterpret_cast<char*>(this), sizeof(Employee));
	if (fin.fail())
	{
		return false;
	}
	return true;
}

void Employee::writeText(std::ostream& ofs = std::cout) const
{
	if (!ofs)
	{
		throw std::runtime_error("Failed to write text data: stream is not valid");
	}
	ofs << "Name: " << name
		<< ", Age: " << age
		<< ", Salary: " << salary
		<< ", Experience: " << yearsOfExperience
		<< "\n";
	if (!ofs)
	{
		throw std::runtime_error("Failed to write text data: write operation failed");
	}
}

void Employee::validateName(const char* name) const
{
	if (strlen(name) == 0)
	{
		throw std::invalid_argument("Name cannot be empty");
	}
	if (strlen(name) >= NameSize)
	{
		throw std::invalid_argument("Name is too long");
	}
}

void Employee::validateAge(int age) const
{
	if (age < 18 || age > 100)
	{
		throw std::invalid_argument("Age must be between 18 and 100");
	}
}

void Employee::validateSalary(double salary) const
{
	if (salary < 0)
	{
		throw std::invalid_argument("Salary cannot be negative");
	}
}

void Employee::validateExperience(int years) const
{
	if (years < 0)
	{
		throw std::invalid_argument("Experience cannot be negative");
	}
	if (years > age - 18)
	{
		throw std::invalid_argument("Experience cannot be greater than age - 18");
	}
}

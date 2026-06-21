#include"Employee.h"
#include"EmployeesIO.h"
#include <filesystem>

bool filterHighSalary(const Employee& e);

bool filterExperienced(const Employee& e);

bool filterYoung(const Employee& e);

int filterEmployees(const Employee* source, int size,
	Employee* dest,
	bool (*predicate)(const Employee&));


int main()
{
    //std::cout << sizeof(Employee) << std::endl;
    const char* binaryFile{ "employees.dat" };
    const char* textFile{ "filtered_employees.txt" };
    Employee data[EmployeesIO::MaxEmployees] =
    {
        Employee("Alice Brown", 30, 1200.0, 6),
        Employee("Bob Smith", 25, 950.0, 3),
        Employee("Charlie Johnson", 40, 1800.0, 12),
        Employee("Diana Young", 28, 1100.0, 5),
        Employee("Evan Lee", 38, 2200.0, 10)
    };

    std::filesystem::path binaryPath = std::filesystem::current_path() / binaryFile;
    if (!std::filesystem::exists(binaryPath))
    {
        std::filesystem::path sourcePath = std::filesystem::path(__FILE__).parent_path() / binaryFile;
        if (std::filesystem::exists(sourcePath))
        {
            binaryPath = sourcePath;
        }
        else
        {
            std::ofstream fout(binaryPath, std::ios::binary | std::ios::trunc);
            EmployeesIO::writeToBinary(fout, data, EmployeesIO::MaxEmployees);
        }
    }

    int total{ 0 };
    std::ifstream fin(binaryPath, std::ios::binary);
    Employee* employees{ EmployeesIO::readFromBinary(fin, total) };
    fin.close();

    Employee* filtered{ new Employee[total] };
    int filteredCount = filterEmployees(employees, total, filtered, filterExperienced);

    std::ofstream out(textFile);
    EmployeesIO::writeToText(out, filtered, filteredCount);
    std::cout << "File '" << textFile << "' have been created.\n";
    delete[] filtered;
    filtered = new Employee[total];
    filteredCount = filterEmployees(employees, total, filtered, filterHighSalary);

    std::ofstream out1("filtered.txt", std::ios::app);
    EmployeesIO::writeToText(out1, filtered, filteredCount);
    std::cout << "File '" << textFile << "' have been created.\n";
    return 0;
}

bool filterHighSalary(const Employee& e)
{
	return e.getSalary() > 1000.0;
}

bool filterExperienced(const Employee& e)
{
	return e.getExperience() > 5;
}

bool filterYoung(const Employee& e)
{
	return e.getAge() < 30;
}

int filterEmployees(const Employee* source, int size,
	Employee* dest,
	bool (*predicate)(const Employee&))
{
	int count = 0;
	for (int i = 0; i < size; ++i)
	{
		if (predicate(source[i]))
		{
			dest[count++] = source[i];
		}
	}
	return count;
}

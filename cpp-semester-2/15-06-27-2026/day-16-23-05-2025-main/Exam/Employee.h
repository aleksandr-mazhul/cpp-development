#pragma once
#include <iostream>
#include <fstream>

class Employee
{
private:
	static const int NameSize = 50;
	char name[NameSize];
	int age;
	double salary;
	int yearsOfExperience;

	void validateName(const char* n) const;
	void validateAge(int a) const;
	void validateSalary(double s) const;
	void validateExperience(int y) const;

public:
	Employee();
	Employee(const char* n, int a, double s, int y);

	const char* getName() const;
	int getAge() const;
	double getSalary() const;
	int getExperience() const;

	void writeBinary(std::ofstream& fout) const;
	bool readBinary(std::ifstream& fin);
	void writeText(std::ostream& out) const;
};
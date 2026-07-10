#pragma once
#include <string>

class Employee
{
  public:
    static constexpr int NameSize = 50;

    Employee();
    Employee(const std::string& name, int age, double salary, int yearsOfExperience);

    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] int getAge() const;
    [[nodiscard]] double getSalary() const;
    [[nodiscard]] int getYearsOfExperience() const;

  private:
    std::string name;
    int age{};
    double salary{};
    int yearsOfExperience{};


    static void validateName(const std::string& name);
    static void validateAge(int age);
    static void validateSalary(double salary);
    static void validateYearsOfExperience(int yearsOfExperience,int age);
};

std::ostream& operator<<(std::ostream& out, const Employee& employee);

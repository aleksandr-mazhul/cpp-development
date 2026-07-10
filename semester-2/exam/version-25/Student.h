#pragma once
#include <string>
#include <utility>

class Student
{
  public:
    Student() = default;

    Student(int id, std::string  name, double averageGrade)
        : id(id)
        , name(std::move(name))
        , averageGrade(averageGrade)
    {
    }

    [[nodiscard]] int getId() const;
    [[nodiscard]] const std::string& getName() const;
    [[nodiscard]] double getAverageGrade() const;
    [[nodiscard]] std::string toString() const;

  private:
    int id{};
    std::string name{};
    double averageGrade{};
};

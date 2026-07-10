#include "Student.h"

#include <sstream>

int Student::getId() const
{
    return id;
}

const std::string& Student::getName() const
{
    return name;
}

double Student::getAverageGrade() const
{
    return averageGrade;
}

std::string Student::toString() const
{
    std::ostringstream out;
    out << id << ","  << name << ","  << averageGrade << "\n";
    return out.str();
}

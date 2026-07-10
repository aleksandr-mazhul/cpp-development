#pragma once
#include <vector>
#include "Student.h"
template <typename Predicate>
std::vector<Student> filterStudents(const std::vector<Student>& students,Predicate predicate)
{
    std::vector<Student> result;
    for (const Student& student : students)
    {
        if (predicate(student))
        {
            result.push_back(student);
        }
    }
    return result;
}


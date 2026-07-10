#pragma once
#include <vector>
#include "Employee.h"
template <typename Predicate>
std::vector<Employee> filterEmployees(const std::vector<Employee>& employees,Predicate predicate)
{
    std::vector<Employee> result;
    for (const Employee& employee : employees)
    {
        if (predicate(employee))
        {
            result.push_back(employee);
        }
    }
    return result;
}


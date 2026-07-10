#pragma once
#include "Student.h"

#include <vector>

class StudentIO
{
  public:
    static std::vector<Student> readFromBinary(std::istream& in);
    static void writeToCSV(const std::vector<Student>& students, std::ostream& out);

  private:
    static bool readStudent(std::istream& in, Student& student);
    static bool readExact(std::istream& in,char* buffer, std::streamsize size);
};

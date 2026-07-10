#include "Student.h"
#include "FeltreStudents.h"
#include "StudentIO.h"

#include <iostream>
#include <istream>
#include <fstream>
#include <ostream>
int main()
{
    try
    {
        std::ifstream fin("/Users/alexandermazhul/projects/archive/cpp-development/semester-2/exam/version-25/students.dat", std::ios::binary);
        std::vector<Student> students = StudentIO::readFromBinary(fin);

        std::vector<Student> filteredStudents = filterStudents(students,[](const Student& student)
        {
            return student.getAverageGrade() > 1;
        });

        std::ofstream out("/Users/alexandermazhul/projects/archive/cpp-development/semester-2/exam/version-25/students.csv");
        StudentIO::writeToCSV(filteredStudents,out);


    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
    }



}

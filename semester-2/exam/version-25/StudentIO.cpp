#include "StudentIO.h"

#include <istream>

std::vector<Student> StudentIO::readFromBinary(std::istream& in)
{
    std::vector<Student> students;
    Student student;
    while (readStudent(in,student))
    {
        students.push_back(student);
    }
    return students;
}

void StudentIO::writeToCSV(const std::vector<Student>& students, std::ostream& out)
{
    out << "ID," <<"Name," <<"AverageGrade" << "\n";
    for (const Student& student : students)
    {
        out << student.toString();
    }
}

bool StudentIO::readStudent(std::istream& in, Student& student)
{
    if (!in)
    {
        throw std::runtime_error("Can't open binary file: input stream is not valid");
    }

    int id{};
    if (!readExact(in, reinterpret_cast<char*>(&id), sizeof(id)))
    {
        return false;
    }

    uint16_t nameLength{};
    if (!readExact(in, reinterpret_cast<char*>(&nameLength), sizeof(uint16_t)))
    {
        throw std::runtime_error("failed in process of reading binary file");
    }

    std::string name(nameLength, '\0');
    double averageGrade{};

    if (!readExact(in, name.data(), nameLength)
        || !readExact(in, reinterpret_cast<char*>(&averageGrade), sizeof(averageGrade)))
    {
        throw std::runtime_error("failed in process of reading binary file");
    }

        student = Student(id, name, averageGrade);


    return true;
}

bool StudentIO::readExact(std::istream& in, char* buffer, const std::streamsize size)
{
    in.read(buffer, size);
    return in.gcount() == size;
}

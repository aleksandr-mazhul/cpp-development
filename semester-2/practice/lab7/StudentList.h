#pragma once

#include "Comparators.h"

#include <array>
#include <iosfwd>
#include <string>
#include <vector>

struct StudentRecord
{
    std::string surname;
    std::string firstName;
    std::array<int, 5> grades{};

    [[nodiscard]] double averageGrade() const;
};

struct ListNode
{
    StudentRecord data;
    ListNode* next{nullptr};
};

class StudentList
{
public:
    StudentList() = default;
    ~StudentList();

    StudentList(const StudentList&) = delete;
    StudentList& operator=(const StudentList&) = delete;

    void clear();
    [[nodiscard]] bool isEmpty() const;

    void createFromKeyboard();
    void print(std::ostream& os) const;
    void printColored(std::ostream& os) const;

    void append(const StudentRecord& student);
    void sortByAverage(const AverageComparator& compare);
    void insertSorted(const StudentRecord& student, const AverageComparator& compare);
    void insertSortedFromKeyboard(const AverageComparator& compare);

    [[nodiscard]] std::vector<double> averages() const;
    [[nodiscard]] std::vector<std::string> surnames() const;

private:
    ListNode* head{nullptr};
};

StudentRecord readStudentFromKeyboard(std::istream& in);
void printStudent(const StudentRecord& student, std::ostream& os, int index);
void printStudentColored(const StudentRecord& student, std::ostream& os, int index);

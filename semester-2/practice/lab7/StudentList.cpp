#include "StudentList.h"

#include "ConsoleColors.h"

#include <iostream>
#include <stdexcept>

namespace
{
    constexpr int MIN_GRADE = 1;
    constexpr int MAX_GRADE = 10;

    void validateGrade(int grade)
    {
        if (grade < MIN_GRADE || grade > MAX_GRADE)
        {
            throw std::invalid_argument(
                "Ошибка: оценка должна быть в диапазоне [" + std::to_string(MIN_GRADE) + ", "
                + std::to_string(MAX_GRADE) + "].");
        }
    }
}

double StudentRecord::averageGrade() const
{
    int sum = 0;
    for (int g : grades)
    {
        sum += g;
    }
    return static_cast<double>(sum) / grades.size();
}

StudentList::~StudentList()
{
    clear();
}

void StudentList::clear()
{
    while (head)
    {
        ListNode* next = head->next;
        delete head;
        head = next;
    }
}

bool StudentList::isEmpty() const
{
    return head == nullptr;
}

void StudentList::append(const StudentRecord& student)
{
    ListNode* node = new ListNode{student, nullptr};
    if (!head)
    {
        head = node;
        return;
    }

    ListNode* cur = head;
    while (cur->next)
    {
        cur = cur->next;
    }
    cur->next = node;
}

void StudentList::createFromKeyboard()
{
    clear();

    int count = 0;
    std::cout << "Введите количество студентов: ";
    std::cin >> count;

    if (count <= 0)
    {
        throw std::invalid_argument("Ошибка: количество студентов должно быть положительным.");
    }

    for (int i = 0; i < count; ++i)
    {
        std::cout << "\n--- Студент " << (i + 1) << " ---\n";
        append(readStudentFromKeyboard(std::cin));
    }
}

void StudentList::print(std::ostream& os) const
{
    if (!head)
    {
        os << "Список пуст.\n";
        return;
    }

    int index = 1;
    for (const ListNode* current = head; current != nullptr; current = current->next)
    {
        printStudent(current->data, os, index++);
    }
}

void StudentList::printColored(std::ostream& os) const
{
    if (isEmpty())
    {
        os << Color::dim << "  (список пуст)\n" << Color::reset;
        return;
    }

    int index = 1;
    for (const ListNode* current = head; current != nullptr; current = current->next)
    {
        printStudentColored(current->data, os, index++);
    }
}

void StudentList::sortByAverage(const AverageComparator& compare)
{
    if (head == nullptr || head->next == nullptr)
    {
        return;
    }

    ListNode* sorted = head;
    ListNode* current = head->next;
    sorted->next = nullptr;

    while (current != nullptr)
    {
        ListNode* next = current->next;

        if (compare(current->data.averageGrade(), sorted->data.averageGrade()))
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            ListNode* prev = sorted;
            while (prev->next != nullptr
                   && !compare(current->data.averageGrade(), prev->next->data.averageGrade()))
            {
                prev = prev->next;
            }

            current->next = prev->next;
            prev->next = current;
        }

        current = next;
    }

    head = sorted;
}

void StudentList::insertSorted(const StudentRecord& student, const AverageComparator& compare)
{
    ListNode* node = new ListNode{student, nullptr};

    if (head == nullptr || compare(student.averageGrade(), head->data.averageGrade()))
    {
        node->next = head;
        head = node;
        return;
    }

    ListNode* current = head;
    while (current->next != nullptr
           && !compare(student.averageGrade(), current->next->data.averageGrade()))
    {
        current = current->next;
    }

    node->next = current->next;
    current->next = node;
}

void StudentList::insertSortedFromKeyboard(const AverageComparator& compare)
{
    std::cout << "\n--- Новый студент ---\n";
    insertSorted(readStudentFromKeyboard(std::cin), compare);
}

std::vector<double> StudentList::averages() const
{
    std::vector<double> result;
    for (const ListNode* current = head; current != nullptr; current = current->next)
    {
        result.push_back(current->data.averageGrade());
    }
    return result;
}

std::vector<std::string> StudentList::surnames() const
{
    std::vector<std::string> result;
    for (const ListNode* current = head; current != nullptr; current = current->next)
    {
        result.push_back(current->data.surname);
    }
    return result;
}

StudentRecord readStudentFromKeyboard(std::istream& in)
{
    StudentRecord student;
    std::cout << "Фамилия: ";
    in >> student.surname;
    std::cout << "Имя: ";
    in >> student.firstName;

    std::cout << "Введите 5 оценок (" << MIN_GRADE << "-" << MAX_GRADE << "): ";
    for (int& grade : student.grades)
    {
        in >> grade;
        validateGrade(grade);
    }

    return student;
}

void printStudent(const StudentRecord& student, std::ostream& os, int index)
{
    os << index << ". " << student.surname << ' ' << student.firstName << " | оценки: ";

    for (std::size_t i = 0; i < student.grades.size(); ++i)
    {
        os << student.grades[i];
        if (i + 1 < student.grades.size())
        {
            os << ", ";
        }
    }

    os << " | средний балл: " << student.averageGrade() << '\n';
}

void printStudentColored(const StudentRecord& student, std::ostream& os, int index)
{
    os << Color::white << "  " << index << ". " << Color::cyan << student.surname << ' ' << student.firstName
       << Color::reset << Color::dim << " | оценки: " << Color::reset;

    for (std::size_t i = 0; i < student.grades.size(); ++i)
    {
        os << Color::yellow << student.grades[i] << Color::reset;
        if (i + 1 < student.grades.size())
        {
            os << Color::dim << ", " << Color::reset;
        }
    }

    os << Color::dim << " | средний балл: " << Color::reset << Color::green << student.averageGrade()
       << Color::reset << '\n';
}

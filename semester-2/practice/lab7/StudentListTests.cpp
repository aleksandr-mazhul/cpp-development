#include "StudentListTests.h"

#include "Comparators.h"
#include "ConsoleColors.h"
#include "StudentList.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace
{
    constexpr double EPS = 1e-9;

    int passed = 0;
    int failed = 0;

    void printTestSeparator()
    {
        std::cout << Color::dim << "  ────────────────────────────────────────\n" << Color::reset;
    }

    void beginTest(int number, const char* description)
    {
        printTestSeparator();
        std::cout << Color::white << "  Тест " << number << Color::reset << '\n';
        std::cout << "  " << Color::dim << description << Color::reset << '\n';
    }

    void finishTest(bool ok, const std::string& summary)
    {
        if (ok)
        {
            ++passed;
            std::cout << "  " << Color::green << "[OK]  " << Color::reset << summary << '\n';
        }
        else
        {
            ++failed;
            std::cout << "  " << Color::red << "[FAIL] " << Color::reset << summary << '\n';
        }
    }

    bool isDescending(const AverageComparator& comp)
    {
        return comp(2.0, 1.0);
    }

    StudentRecord makeStudent(const char* surname, const char* firstName, std::initializer_list<int> grades)
    {
        StudentRecord student;
        student.surname = surname;
        student.firstName = firstName;

        std::size_t index = 0;
        for (int grade : grades)
        {
            if (index < student.grades.size())
            {
                student.grades[index++] = grade;
            }
        }

        return student;
    }

    std::string formatSurnames(const std::vector<std::string>& surnames)
    {
        std::ostringstream os;
        for (std::size_t i = 0; i < surnames.size(); ++i)
        {
            os << surnames[i];
            if (i + 1 < surnames.size())
            {
                os << " → ";
            }
        }
        return os.str();
    }

    std::string formatAverages(const std::vector<double>& values)
    {
        std::ostringstream os;
        os << std::fixed << std::setprecision(1);
        for (std::size_t i = 0; i < values.size(); ++i)
        {
            os << values[i];
            if (i + 1 < values.size())
            {
                os << " → ";
            }
        }
        return os.str();
    }

    void printListBlock(const char* label, const StudentList& list)
    {
        std::cout << "  " << Color::blue << label << Color::reset << '\n';
        list.printColored(std::cout);
    }

    void printComparison(const std::string& label, const std::string& expected, const std::string& actual, bool match)
    {
        std::cout << "  " << Color::cyan << label << Color::reset << '\n';
        std::cout << "    " << Color::yellow << "ожидание: " << Color::reset << expected << '\n';
        std::cout << "    " << Color::white << "получено:  " << Color::reset;
        if (match)
        {
            std::cout << Color::green << actual << Color::reset << '\n';
        }
        else
        {
            std::cout << Color::red << actual << Color::reset << '\n';
        }
    }

    bool almostEqual(double lhs, double rhs)
    {
        return std::abs(lhs - rhs) < EPS;
    }

    bool matchesAverages(const std::vector<double>& actual, const std::vector<double>& expected)
    {
        if (actual.size() != expected.size())
        {
            return false;
        }

        for (std::size_t i = 0; i < expected.size(); ++i)
        {
            if (!almostEqual(actual[i], expected[i]))
            {
                return false;
            }
        }

        return true;
    }

    void fillSortedList(StudentList& list, const AverageComparator& compare,
                        std::initializer_list<StudentRecord> students)
    {
        list.clear();
        for (const StudentRecord& student : students)
        {
            list.append(student);
        }
        list.sortByAverage(compare);
    }

    void testSortFractionalAverages(const AverageComparator& compare)
    {
        beginTest(1, "Сортировка: дробные средние (5.6, 6.8, 7.6, 8.4) вперемешку");

        StudentList list;
        list.append(makeStudent("Orlov", "Oleg", {9, 8, 8, 8, 9}));
        list.append(makeStudent("Nguyen", "Nam", {6, 5, 6, 5, 6}));
        list.append(makeStudent("Kuznetsova", "Anna", {8, 7, 8, 8, 7}));
        list.append(makeStudent("Belova", "Daria", {7, 7, 6, 7, 7}));

        printListBlock("До сортировки:", list);
        list.sortByAverage(compare);

        const std::vector<double> expected = isDescending(compare)
            ? std::vector<double>{8.4, 7.6, 6.8, 5.6}
            : std::vector<double>{5.6, 6.8, 7.6, 8.4};
        const std::vector<double> averages = list.averages();
        const bool ok = matchesAverages(averages, expected);

        printListBlock("После сортировки:", list);
        printComparison("Порядок средних баллов", formatAverages(expected), formatAverages(averages), ok);
        finishTest(ok, "Четыре дробных средних выстроены в выбранном порядке");
    }

    void testSortSingleElement(const AverageComparator& compare)
    {
        beginTest(2, "Сортировка: список из одного студента (средний 6.8)");

        StudentList list;
        list.append(makeStudent("Solo", "Maria", {7, 7, 6, 7, 7}));

        printListBlock("До сортировки:", list);
        list.sortByAverage(compare);

        const std::vector<double> expected = {6.8};
        const std::vector<double> averages = list.averages();
        const bool ok = matchesAverages(averages, expected);

        printListBlock("После сортировки:", list);
        printComparison("Порядок средних баллов", formatAverages(expected), formatAverages(averages), ok);
        finishTest(ok, "Один элемент остаётся на месте, список не ломается");
    }

    void testSortEqualAverages(const AverageComparator& compare)
    {
        beginTest(3, "Сортировка: одинаковый средний балл 7.2 — порядок студентов сохраняется");

        StudentList list;
        list.append(makeStudent("Volkov", "Ilya", {7, 7, 8, 7, 7}));
        list.append(makeStudent("Morozov", "Max", {8, 7, 7, 7, 7}));
        list.append(makeStudent("Fedorova", "Eva", {7, 8, 7, 7, 7}));

        printListBlock("До сортировки:", list);
        list.sortByAverage(compare);

        const std::vector<std::string> expectedOrder = {"Volkov", "Morozov", "Fedorova"};
        const std::vector<std::string> surnames = list.surnames();
        const std::vector<double> averages = list.averages();
        const bool orderOk = surnames == expectedOrder;
        const bool averagesOk = averages.size() == 3
                                && almostEqual(averages[0], 7.2)
                                && almostEqual(averages[1], 7.2)
                                && almostEqual(averages[2], 7.2);
        const bool ok = orderOk && averagesOk;

        printListBlock("После сортировки:", list);
        printComparison("Порядок фамилий", formatSurnames(expectedOrder), formatSurnames(surnames), orderOk);
        printComparison("Порядок средних баллов", "7.2 → 7.2 → 7.2", formatAverages(averages), averagesOk);
        finishTest(ok, "При равных средних баллах порядок ввода не меняется");
    }

    void testInsertAtHeadAndTail(const AverageComparator& compare)
    {
        beginTest(4, "Вставка: новый минимум (5.4) и новый максимум (8.8) в отсортированный список");

        StudentList list;
        fillSortedList(list, compare, {
            makeStudent("Nguyen", "Nam", {6, 5, 6, 5, 6}),
            makeStudent("Belova", "Daria", {7, 7, 6, 7, 7}),
            makeStudent("Kuznetsova", "Anna", {8, 7, 8, 8, 7}),
            makeStudent("Orlov", "Oleg", {9, 8, 8, 8, 9}),
        });

        printListBlock("Исходный отсортированный список:", list);

        list.insertSorted(makeStudent("Smirnov", "Stepan", {5, 5, 6, 5, 6}), compare);
        list.insertSorted(makeStudent("Popov", "Pavel", {9, 9, 8, 9, 9}), compare);

        const std::vector<double> expected = isDescending(compare)
            ? std::vector<double>{8.8, 8.4, 7.6, 6.8, 5.6, 5.4}
            : std::vector<double>{5.4, 5.6, 6.8, 7.6, 8.4, 8.8};
        const std::vector<double> averages = list.averages();
        const bool ok = matchesAverages(averages, expected);

        printListBlock("После вставки Smirnov (5.4) и Popov (8.8):", list);
        printComparison("Порядок средних баллов", formatAverages(expected), formatAverages(averages), ok);
        finishTest(ok, "Вставка на края списка сохраняет выбранный порядок");
    }

    void testInsertMiddleAndEqualAverage(const AverageComparator& compare)
    {
        beginTest(5, "Вставка: в середину (7.2) и студент с тем же средним (7.6)");

        StudentList list;
        fillSortedList(list, compare, {
            makeStudent("Nguyen", "Nam", {6, 5, 6, 5, 6}),
            makeStudent("Belova", "Daria", {7, 7, 6, 7, 7}),
            makeStudent("Kuznetsova", "Anna", {8, 7, 8, 8, 7}),
            makeStudent("Orlov", "Oleg", {9, 8, 8, 8, 9}),
        });

        printListBlock("Исходный отсортированный список:", list);

        list.insertSorted(makeStudent("Lebedev", "Lev", {7, 8, 7, 7, 7}), compare);
        list.insertSorted(makeStudent("Gromov", "Grigory", {8, 8, 7, 7, 8}), compare);

        const std::vector<double> expected = isDescending(compare)
            ? std::vector<double>{8.4, 7.6, 7.6, 7.2, 6.8, 5.6}
            : std::vector<double>{5.6, 6.8, 7.2, 7.6, 7.6, 8.4};
        const std::vector<double> averages = list.averages();
        const bool ok = matchesAverages(averages, expected);

        printListBlock("После вставки Lebedev (7.2) и Gromov (7.6):", list);
        printComparison("Порядок средних баллов", formatAverages(expected), formatAverages(averages), ok);
        finishTest(ok, "Вставка в середину и при равном среднем балле");
    }

    void runAllTestsWith(const AverageComparator& compare)
    {
        passed = 0;
        failed = 0;

        std::cout << Color::yellow << "\n=== Автотесты (" << comparatorLabel(compare) << ") ===\n"
                  << Color::reset;

        testSortFractionalAverages(compare);
        testSortSingleElement(compare);
        testSortEqualAverages(compare);
        testInsertAtHeadAndTail(compare);
        testInsertMiddleAndEqualAverage(compare);

        printTestSeparator();
        std::cout << '\n';

        const int total = passed + failed;
        if (failed == 0)
        {
            std::cout << Color::green << "  ИТОГ: все тесты пройдены — " << passed << " из " << total << '\n'
                      << Color::reset;
        }
        else
        {
            std::cout << Color::yellow << "  ИТОГ: пройдено " << passed << " из " << total
                      << Color::red << ", провалено " << failed << '\n' << Color::reset;
        }
    }
}

void runAllTests()
{
    std::cout << Color::magenta << "\nПорядок для автотестов:\n" << Color::reset;
    auto compare = readAverageComparatorFromKeyboard();
    runAllTestsWith(compare);
}

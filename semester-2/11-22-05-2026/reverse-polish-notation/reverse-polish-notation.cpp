#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

bool isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int priority(char op)
{
    if (op == '+' || op == '-')
        return 1;

    if (op == '*' || op == '/')
        return 2;

    return 0;
}

std::string infixToPostfix(const std::string& expression)
{
    std::stack<char, std::vector<char>> operators;
    std::string output;

    std::size_t i = 0;

    while (i < expression.size())
    {
        char ch = expression[i];

        // игнорируем пробелы
        if (std::isspace(static_cast<unsigned char>(ch)))
        {
            ++i;
            continue;
        }

        // число (многозначное)
        if (std::isdigit(static_cast<unsigned char>(ch)))
        {
            while (i < expression.size() && std::isdigit(static_cast<unsigned char>(expression[i])))
            {
                output += expression[i];
                ++i;
            }

            output += ' ';
            continue;
        }

        // переменная (одна буква)
        if (std::isalpha(static_cast<unsigned char>(ch)))
        {
            output += ch;
            output += ' ';
            ++i;
            continue;
        }

        // открывающая скобка
        if (ch == '(')
        {
            operators.push(ch);
            ++i;
            continue;
        }

        // закрывающая скобка
        if (ch == ')')
        {
            while (!operators.empty() && operators.top() != '(')
            {
                output += operators.top();
                output += ' ';
                operators.pop();
            }

            if (operators.empty())
                throw std::runtime_error("лишняя закрывающая скобка");

            operators.pop(); // убрать '('
            ++i;
            continue;
        }

        // оператор
        if (isOperator(ch))
        {
            while (!operators.empty() && operators.top() != '('
                && priority(operators.top()) >= priority(ch))
            {
                output += operators.top();
                output += ' ';
                operators.pop();
            }

            operators.push(ch);
            ++i;
            continue;
        }

        throw std::runtime_error("неизвестный символ в выражении");
    }

    // очистка стека
    while (!operators.empty())
    {
        if (operators.top() == '(')
            throw std::runtime_error("не закрыта открывающая скобка");

        output += operators.top();
        output += ' ';
        operators.pop();
    }

    // убрать последний пробел
    if (!output.empty())
        output.pop_back();

    return output;
}

struct TestCase
{
    std::string infix;
    std::string expected;
};

int main()
{
    std::vector<TestCase> tests = {
        {"(A + B) * (C - D) / E", "A B + C D - * E /"},
        {"a + b * (c - d) / e + f", "a b c d - * e / + f +"},
        {"x*y+z", "x y * z +"},
        {"a+b*c", "a b c * +"},
        {"(a+b)*(c-d)", "a b + c d - *"},
        {"p/(q-r)*s+t", "p q r - / s * t +"},
        {"10 + 25 * 3", "10 25 3 * +"},
        {"100*(2+12)/14", "100 2 12 + * 14 /"}
    };

    for (const TestCase& test : tests)
    {
        try
        {
            std::string result = infixToPostfix(test.infix);

            if (result == test.expected)
            {
                std::cout << "[OK]   " << test.infix << " -> " << result << '\n';
            }
            else
            {
                std::cout << "[FAIL] " << test.infix << '\n';

                std::cout << "  expected: " << test.expected << '\n';
                std::cout << "  got:      " << result << '\n';
            }
        }
        catch (const std::exception& e)
        {
            std::cout << "[ERROR] " << test.infix << " : " << e.what() << '\n';
        }
    }

    return 0;
}

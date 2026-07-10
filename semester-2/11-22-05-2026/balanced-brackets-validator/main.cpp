#include <iostream>
#include <stack>
#include <string>
#include <vector>

bool isMatchingPair(char open, char close);
bool isBalancedBrackets(const std::string& text);
bool isBalancedBracketsByReduction(const std::string& text);
void runBuiltInTests();

int main()
{
    runBuiltInTests();
    std::cout << "\n";
    std::cout << "----------------------------------------\n";
    std::cout << "Enter a string with brackets: ";
    const std::string example = "{[()]}(()[])";
    std::string input;
    std::getline(std::cin, input);
    if (input.empty())
    {
        input = example;
        std::cout << "Using example: " << input << "\n";
    }

    if (isBalancedBrackets(input))
    {
        std::cout << "Brackets are balanced\n";
    }
    else
    {
        std::cout << "Brackets are NOT balanced\n";
    }

    return 0;
}

void runBuiltInTests()
{
    const std::vector<std::string> testCases = {
        "{[()]}",
        "{[()]}(()[])",
        "(((())))",
        "[{()}](){}",
        "",
        "abc(def)[x]{y}",
        "([{}])()[]{}",
        "(",
        "}",
        "([)]",
        "{[(])}",
        "(()",
        "())",
        "][",
        "{[()]}]",
        "((a+b)*[c-d])"
    };

    std::cout << "Built-in tests:\n";
    for (const auto& test : testCases)
    {
        const bool byStack = isBalancedBrackets(test);
        const bool byReduction = isBalancedBracketsByReduction(test);
        std::cout << "  \"" << test << "\" -> "
            << "stack: " << (byStack ? "passed" : "failed")
            << ", reduction: " << (byReduction ? "passed" : "failed") << "\n";
    }
}

bool isMatchingPair(char open, char close)
{
    return (open == '(' && close == ')') || (open == '[' && close == ']')
        || (open == '{' && close == '}');
}

bool isBalancedBrackets(const std::string& text)
{
    std::stack<char> stack;
    for (char c : text)
    {
        if (c == '(' || c == '{' || c == '[')
        {
            stack.push(c);
        }
        else
        {
            if (c == ')' || c == '}' || c == ']')
            {
                if (stack.empty() || !isMatchingPair(stack.top(), c))
                {
                    return false;
                }
                stack.pop();
            }
        }
    }

    return stack.empty();
}

bool isBalancedBracketsByReduction(const std::string& text)
{
    std::string helperString;
    helperString.reserve(text.size());
    for (char c : text)
    {
        if (c == '(' || c == '{' || c == '[' || c == ')' || c == '}' || c == ']')
        {
            helperString.push_back(c);
        }
    }

    bool changed = true;
    while (changed)
    {
        changed = false;
        std::size_t pos = std::string::npos;
        while ((pos = helperString.find("()")) != std::string::npos)
        {
            helperString.erase(pos, 2);
            changed = true;
        }

        pos = std::string::npos;
        while ((pos = helperString.find("[]")) != std::string::npos)
        {
            helperString.erase(pos, 2);
            changed = true;
        }

        pos = std::string::npos;
        while ((pos = helperString.find("{}")) != std::string::npos)
        {
            helperString.erase(pos, 2);
            changed = true;
        }
    }
    return helperString.empty();
}

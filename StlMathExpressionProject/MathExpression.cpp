#include "MathExpression.h"
#include <stack>

double& MathExpression::operator[](std::string key)
{
    return variables[key];
}

int MathExpression::CheckedBrackets()
{
    std::stack<char> bracketsStack;

    int position{};

    for (auto symbol : infixExpression)
    {
        position++;

        if (brackets.find(symbol) == std::string::npos)
            continue;

        if (openBrackets.find(symbol) != std::string::npos)
        {
            bracketsStack.push(symbol);
            continue;
        }

        if (bracketsStack.empty())
            return position;

        int typeCloseBracket = closeBrackets.find(symbol);
        int typeOpenBracket = openBrackets.find(bracketsStack.top());

        if (typeOpenBracket != typeCloseBracket)
            return position;
    }

    if (!brackets.empty())
        return position;

    return -1;
}

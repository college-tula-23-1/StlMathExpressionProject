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

void MathExpression::CreatePostfix()
{
    for (int position{};
        position < infixExpression.length();
        position++)
    {
        char symbol = infixExpression[position];

        // white spaces ignore
        if (isspace(symbol)) continue;

        // reading numbers
        if (isdigit(symbol))
        {
            std::string number = "";
            while ((isdigit(symbol) ||
                symbol == '.' ||
                tolower(symbol) == 'e') &&
                position < infixExpression.length())
            {
                if (tolower(symbol) == 'e' &&
                    infixExpression[position + 1] == '-')
                {
                    number.push_back(symbol);
                    number.push_back(infixExpression[position + 1]);
                    position += 2;
                    symbol = infixExpression[position];
                }
                else
                {
                    number.push_back(symbol);
                    symbol = infixExpression[++position];
                }
            }
            number.push_back('#');
            postfixExpression.append(number);
            position--;
            continue;
        }
    }
}

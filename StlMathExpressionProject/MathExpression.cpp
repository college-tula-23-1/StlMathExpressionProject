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
    std::stack<char> stack;
    bool isUnare{ true };

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
            isUnare = false;
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

        // reading vars and funcs
        if (isalpha(symbol) || symbol == '_')
        {
            isUnare = false;
            std::string var = "";
            var.push_back(symbol);
            
            symbol = infixExpression[++position];

            while ((isalnum(symbol) || symbol == '_') 
                && position < infixExpression.length())
            {
                var.push_back(symbol);
                symbol = infixExpression[++position];
            }
            if (functions.contains(var))
                stack.push(functions[var]);
            else
            {
                if (variables[var] < 0)
                    postfixExpression.push_back('~');

                postfixExpression.append(std::to_string(abs(variables[var])));
                postfixExpression.push_back('#');
            }
        }

        // open brackets
        if (openBrackets.find(symbol) != std::string::npos)
        {
            stack.push(symbol);
            isUnare = true;
        }
            

        // close brackets
        if (closeBrackets.find(symbol) != std::string::npos)
        {
            isUnare = false;
            while (openBrackets.find(stack.top()) == std::string::npos)
            {
                postfixExpression.push_back(stack.top());
                stack.pop();
            }
            stack.pop();
        }

        // multiplex operators
        if (multOperations.find(symbol) != std::string::npos)
        {
            isUnare = true;
            while (!stack.empty() && multOperations.find(stack.top()) != std::string::npos)
            {
                postfixExpression.push_back(stack.top());
                stack.pop();
            }
            stack.push(symbol);
        }

        // additive operators
        if (addOperations.find(symbol) != std::string::npos)
        {
            if (symbol == '-' && isUnare)
            {
                postfixExpression.push_back('~');
                isUnare = false;
            }
            else
            {
                isUnare = true;
                while (!stack.empty() && openBrackets.find(stack.top()) == std::string::npos)
                {
                    postfixExpression.push_back(stack.top());
                    stack.pop();
                }
                stack.push(symbol);
            }
        }
    }
    while (!stack.empty())
    {
        postfixExpression.push_back(stack.top());
        stack.pop();
    }
}

double MathExpression::Calculate()
{
    std::stack<double> stack;

    for (int position{}; position < postfixExpression.length(); position++)
    {
        char symbol = postfixExpression[position];
        if (isdigit(symbol) || symbol == '~')
        {
            std::string number{ "" };
            while (symbol != '#')
            {
                if (symbol == '~')
                    symbol = '-';
                number.push_back(symbol);
                symbol = postfixExpression[++position];
            }
            stack.push(std::stod(number));
        }
        
        if (operations.find(symbol) != std::string::npos)
        {
            double result{};
            
            double rightOperand = stack.top(); stack.pop();
            double leftOperand = stack.top(); stack.pop();

            switch (symbol)
            {
            case '+': result = leftOperand + rightOperand; break;
            case '-': result = leftOperand - rightOperand; break;
            case '*': result = leftOperand * rightOperand; break;
            case '/': result = leftOperand / rightOperand; break;
            default:
                break;
            }
            stack.push(result);
        }

        if (functionsChar.find(symbol) != std::string::npos)
        {
            double result{};
            double operand{ stack.top() }; stack.pop();
            switch (symbol)
            {
            case 's': result = sin(operand); break;
            case 'c': result = cos(operand); break;
            case 'l': result = log(operand); break;
            default:
                break;
            }
            stack.push(result);
        }
    }

    return stack.top();
}


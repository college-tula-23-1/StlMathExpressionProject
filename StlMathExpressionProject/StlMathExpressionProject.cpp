// StlMathExpressionProject.cpp
#include "MathExpression.h"

#include <iostream>
#include <map>

int main()
{
    MathExpression expr;
    expr["a"] = 10;
    expr["abc"] = 123;
    expr["a"] = 100;

    for (auto item : expr.Variables())
    {
        std::cout << item.first << " -> " << item.second << "\n";
    }
}

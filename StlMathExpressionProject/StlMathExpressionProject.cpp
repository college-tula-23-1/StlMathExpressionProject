// StlMathExpressionProject.cpp
#include "MathExpression.h"

#include <iostream>
#include <map>

int main()
{
    MathExpression expr("(123 - 78.09)*8e-3 + 0.002 / 56.909E2");
    expr.CreatePostfix();

    std::cout << expr.PostfixExpression() << "\n";
    
}

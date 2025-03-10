// StlMathExpressionProject.cpp
#include "MathExpression.h"

#include <iostream>
#include <map>

int main()
{
    MathExpression expr("(-5.5 + -2) * -3 + (-7 + 9)");
    expr.CreatePostfix();

    std::cout << expr.PostfixExpression() << "\n";
    std::cout << expr.Calculate() << "\n";
    
}

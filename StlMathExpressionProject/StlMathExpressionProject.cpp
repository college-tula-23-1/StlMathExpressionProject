// StlMathExpressionProject.cpp
#include "MathExpression.h"

#include <iostream>
#include <map>

int main()
{
    MathExpression expr("(a + 10) * sin(b_2) - _count");
    expr["a"] = 20;
    expr["b_2"] = 3.1416 / 6;
    expr["_count"] = 0.2e2;

    expr.CreatePostfix();

    std::cout << expr.PostfixExpression() << "\n";
    std::cout << expr.Calculate() << "\n";
    
}

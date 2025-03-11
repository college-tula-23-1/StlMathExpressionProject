#pragma once
#include <string>
#include <map>

class MathExpression
{
	std::string infixExpression;
	std::string postfixExpression;

	std::map<std::string, double> variables;
	std::map<std::string, char> functions;
	std::string functionsChar = "";

	const std::string openBrackets  = "({[";
	const std::string closeBrackets = ")}]";
	const std::string brackets = openBrackets + closeBrackets;

	const std::string addOperations  = "+-";
	const std::string multOperations = "*/";
	const std::string operations = addOperations + multOperations;

public:
	MathExpression() : MathExpression("") {};

	MathExpression(std::string infixExpression)
		: infixExpression{ infixExpression },
		postfixExpression{ "" } 
	{
		functions["sin"] = 's';
		functions.insert(std::pair<std::string, char>{ "cos", 'c' });
		functions["log"] = 'l';

		for (auto item : functions)
			functionsChar.push_back(item.second);
	}

	std::map<std::string, double>& Variables() { return variables; }

	const std::string OpenBrackets() const { return openBrackets; }
	const std::string CloseBrackets() const { return closeBrackets; }
	const std::string Brackets() const { return brackets; }

	const std::string AddOperations() const { return addOperations; }
	const std::string MultOperations() const { return multOperations; }

	std::string& InfixExpression() { return infixExpression; }
	std::string PostfixExpression() const { return postfixExpression; }

	double& operator[](std::string key);

	int CheckedBrackets();	
	void CreatePostfix();
	double Calculate();
};


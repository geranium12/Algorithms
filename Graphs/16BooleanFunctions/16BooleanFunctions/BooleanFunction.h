#pragma once
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

class BooleanFunction
{
private:
	string postfixStr;
	vector<short> variables;
	vector<bool> valueVector;

	void postfix(string);
	void calcValueVector();
	bool calcValue(vector<bool>);
	int getPriority(char);
	int skipSymbols(char);

public:
	BooleanFunction(string);
	string getPostfixStr();
	vector<bool> getValueVector();
};


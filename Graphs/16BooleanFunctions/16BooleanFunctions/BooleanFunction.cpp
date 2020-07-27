#include "BooleanFunction.h"

BooleanFunction::BooleanFunction(string str)
{
	postfix(str);
	if (variables.size())
	{
		calcValueVector();
	}
	else
	{
		vector<bool> v;
		bool a = calcValue(v);
		valueVector.push_back(a);
	}
}

string BooleanFunction::getPostfixStr()
{
	return postfixStr;
}

vector<bool> BooleanFunction::getValueVector()
{
	return valueVector;
}

int BooleanFunction::getPriority(char c)
{
	switch (c)
	{
	case '~':
		return 1;
	case '|':
		return 2;
	case '!':
		return 3;
	case '/':
		return 4;
	case '\\':
		return 5;
	case '^':
		return 6;
	case '-':
		return 7;
	case '<':
		return 8;
	case '(':
		return 9;
	default:
		return 0;
	}
}

int BooleanFunction::skipSymbols(char c)
{
	switch (c)
	{
	case '/': case '\\': case '-':
		return 1;
	case '<':
		return 2;
	default:
		return 0;
	}
}

void BooleanFunction::postfix(string str)
{
	stack <char> st;

	for (size_t i = 0; i < str.length(); i++)
	{
		char c = str[i];
		switch (c)
		{
		case '~':
		{
			st.push(c);
			break;
		}
		case '(':
		{
			st.push(c);
			break;
		}
		case ')':
		{
			while (st.top() != '(')
			{
				postfixStr += st.top();
				st.pop();
			}
			postfixStr += ' ';
			st.pop();
			break;
		}
		case 'x':
		{
			i++;
			string number;
			while (isdigit(str[i]))
			{
				number += str[i];
				i++;
			}
			i--;
			variables.push_back(stoi(number) - 1);
			postfixStr += 'z';
			postfixStr += ' ';
			break;
		}
		case ' ':
		{
			break;
		}
		default:
		{
			if (isdigit(c))
			{
				postfixStr += c;
				postfixStr += ' ';
			}
			else
			{
				while (!st.empty() && getPriority(st.top()) <= getPriority(c))
				{
					//if (st.top() != '(')
					//{
					postfixStr += st.top();
					//}
					st.pop();
				}
				postfixStr += ' ';
				st.push(c);
				i += skipSymbols(c);
			}
		}
		}
	}

	while (!st.empty())
	{
		if (st.top() != '(')
		{
			postfixStr += st.top();
			//postfixStr += ' ';
		}
		st.pop();
	}
}

void BooleanFunction::calcValueVector()
{
	short n = variables[0];
	for (size_t i = 1; i < variables.size(); i++)
	{
		if (variables[i] > n)
		{
			n = variables[i];
		}
	}

	n++;
	int k = 1;
	k <<= n;
	vector<bool> row(n);
	valueVector.resize(k);
	valueVector[0] = calcValue(row);
	n--;

	for (int i = 1; i < k; i++)
	{
		int x = i;
		short j = 0;
		while (x)
		{
			row[n - j] = x & 1;
			x >>= 1;
			j++;
		}
		valueVector[i] = calcValue(row);
	}
}

bool BooleanFunction::calcValue(vector<bool> v)
{
	stack <bool> st;
	size_t i, j;
	i = j = 0;
	while (i < postfixStr.length())
	{
		char c = postfixStr[i];
		bool a, b;
		switch (c)
		{
		case '0': case '1':
		{
			st.push(c - '0');
			break;
		}
		case 'z':
		{
			st.push(v[variables[j]]);
			j++;
			break;
		}
		case '~':
		{
			a = st.top();
			st.pop();
			a = !a;
			st.push(a);
			break;
		}
		case '|':
		{
			b = st.top();
			st.pop();
			a = st.top();
			st.pop();
			a = !(a & b);
			st.push(a);
			break;
		}
		case '!':
		{
			b = st.top();
			st.pop();
			a = st.top();
			st.pop();
			a = !(a | b);
			st.push(a);
			break;
		}
		case '\\':
		{
			b = st.top();
			st.pop();
			a = st.top();
			st.pop();
			st.push(a | b);
			break;
		}
		case '/':
		{
			b = st.top();
			st.pop();
			a = st.top();
			st.pop();
			st.push(a & b);
			break;
		}
		case '^':
		{
			b = st.top();
			st.pop();
			a = st.top();
			st.pop();
			st.push(a ^ b);
			break;
		}
		case '-':
		{
			b = st.top();
			st.pop();
			a = st.top();
			st.pop();
			a = (!a) | b;
			st.push(a);
			break;

		}
		case '<':
		{
			b = st.top();
			st.pop();
			a = st.top();
			st.pop();
			a = (!a & !b) | (a & b);
			st.push(a);
			break;
		}
		}
		i++;
	}

	bool res = st.top();
	st.pop();
	return res;
}
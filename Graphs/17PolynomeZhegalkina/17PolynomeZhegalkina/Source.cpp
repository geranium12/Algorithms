#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

string postfixStr;
vector<short> variables;
vector<bool> valueVector;
short max;

int getPriority(char c)
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

int skipSymbols(char c)
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

void postfix(string str)
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
			}
			else
			{
				while (!st.empty() && getPriority(st.top()) <= getPriority(c))
				{
					postfixStr += st.top();
					st.pop();
				}
				st.push(c);
				i += skipSymbols(c);
			}
		}
		}
	}

	while (!st.empty())
	{
		switch (st.top())
		{
		case '(':
			break;
		default:
			postfixStr += st.top();
		}
		st.pop();
	}
}

bool calcValue(vector<bool> v)
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

void calcValueVector()
{
	max = variables[0];
	for (size_t i = 1; i < variables.size(); i++)
	{
		if (variables[i] > max)
		{
			max = variables[i];
		}
	}

	max++;
	int k = 1;
	k <<= max;
	vector<bool> row(max);
	valueVector.resize(k);
	valueVector[0] = calcValue(row);
	max--;

	for (int i = 1; i < k; i++)
	{
		int x = i;
		short j = 0;
		while (x)
		{
			row[max - j] = x & 1;
			x >>= 1;
			j++;
		}

		valueVector[i] = calcValue(row);
	}
}


int main()
{
	ifstream fin("input.txt");
	ofstream fout("output.txt");

	string str;
	getline(fin, str);

	postfix(str);

	switch (variables.size())
	{
	case 0:
	{
		vector<bool> v;
		bool a = calcValue(v);
		valueVector.push_back(a);
		break;
	}
	default:
	{
		calcValueVector();
		max++;
		int n = 1;
		n <<= max;
		int j;
		for (int k = 2; k <= n; k <<= 1)
		{
			j = 0;
			for (int i = 0; i < n >> 1; i++)
			{
				//cout << i % (n / k) + j * (n / (k >> 1)) << " " << (i % (n / k)) + n / k + j * (n / (k >> 1)) << endl;
				int z = (n / k);
				int y = i % z;
				int x = y + j * (n / (k >> 1));
				valueVector[x + z] = valueVector[x + z] ^ valueVector[x];
				if (y == z - 1)
				{
					j++;
				}
			}
		}
	}
	}

	for (int i = 0; i < valueVector.size(); i++)
	{
		fout << valueVector[i];
	}
	return 0;
}
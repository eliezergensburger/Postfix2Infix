// from https://www.geeksforgeeks.org/postfix-to-infix/
// CPP program to find infix for 
// a given postfix. 
#include <iostream>
#include<algorithm>
#include <stack>
#include <vector>
#include <string>

using namespace std;

bool isnumber(char * exp, int&i, int &val);
bool isOperand(char x);
bool is_number(const string& s);
bool is_numberOsher(const string& s);
bool isOperandValue(string x);
string getInfix(string exp);

template <class Container>
void split4(const string& str, Container& cont, const string& delims = " ");


template <class Container>
void split4(const string& str, Container& cont,	const string& delims)
{
	size_t current, previous = 0;
	string token;
	current = str.find_first_of(delims);
	while (current != string::npos) {
		token = str.substr(previous, current - previous);
		if (token.length() > 0)
		{
			cont.push_back(token);
		}
		previous = current + 1;
		current = str.find_first_of(delims, previous);
	}
	cont.push_back(str.substr(previous, current - previous));
}

int evaluatePostfix(char* exp)
{
	// Create a stack of capacity equal to expression size  
	stack<string> stack;
	int num;
	int i;
	// Scan all characters one by one  
	for (i = 0; exp[i]; ++i)
	{
		//if the character is blank space then continue  
		if (exp[i] == ' ')continue;

		// If the scanned character is an  
		// operand (number here),extract the full number  
		// Push it to the stack.  
		num = 0;
		if (isnumber(exp, i, num))
		{
			//itoa(num, elem.data, 10);
			stack.push(to_string(num));
		}
		else if (exp[i] == '(')
		{
			stack.push(to_string(exp[i]));
		}
		// If the scanned character is an operator, pop two  
		// elements from stack apply the operator  
		else if (exp[i] == ')')
		{
			stack.push(to_string(exp[i]));
			stack.pop();

			int val1 = atoi(stack.top().c_str());
			stack.pop();
			int val2 = atoi(stack.top().c_str());
			stack.pop();

			switch (exp[i])
			{
			case '+': num = val2 + val1;break;
			case '-': num = val2 - val1; break;
			case '*': num = val2 * val1; break;
			case '/': num = val2 / val1; break;
			}
			stack.push(to_string(num));
		}
	}
	return atoi(stack.top().c_str());
}

bool isOperand(char x)
{
	return (x >= 'a' && x <= 'z') ||
		(x >= 'A' && x <= 'Z');
}
bool isnumber(char * exp, int&i, int &val)
{
	int num;

	if (!isdigit(exp[i]))
		return false;
	num = 0;
	//extract full number  
	while (isdigit(exp[i]))
	{
		num = num * 10 + (int)(exp[i] - '0');
		++i;
	}
	--i;
	val = num;
	return true;
}

bool is_number(const string& s)
{
	return !s.empty() && find_if(s.begin(), s.end(), [](char c) { return !isdigit(c); }) == s.end();
}

bool is_numberOsher(const string& s)
{
	if (s.empty()) return false;
	return (all_of(s.begin(), s.end(), isdigit));
}

bool isOperandValue(string x)
{
	return false;
}

//Get Infix for a given postfix 
//expression 
string getInfix(string exp)
{
	stack<string> s;

	for (int i = 0; exp[i] != '\0'; i++)
	{
		//Push operands 
		if (isOperand(exp[i]))
		{
			string op(1, exp[i]);
			s.push(op);
		}

		//We assume that input is 
		//a valid postfix and expect 
		//an operator. 
		else
		{
			string op1 = s.top();
			s.pop();
			string op2 = s.top();
			s.pop();
			s.push("(" + op2 + exp[i] + op1 + ")");
		}
	}

	//There must be a single element 
	//in stack now which is the required 
	//infix. 
	string result = s.top();
	return result;
}

ostream& operator<<(ostream& out, const string& str)
{
	out << str.c_str();
	return out;
}
// Driver code 
int main()
{
	//string exp = "ab*c+";
	//cout << getInfix(exp);
	string str = "- This, a )samp(le s;tring.";
	string delims = " -,.)(;";
	vector<string> s;
	split4<vector<string>>(str, s, delims);
	for (auto st : s)
	{
		cout << st << endl;
	}
	system("pause");
	return 0;
}

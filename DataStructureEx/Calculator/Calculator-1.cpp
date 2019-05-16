
#include<iostream>
#include<string>

using namespace std;

template<class T>
class stack
{
private:
	int top_n;
	int maxtop_n;
	T * st;
public:
	stack(int maxstacksize = 10)
	{
		maxtop_n = maxstacksize - 1;
		st = new T[maxstacksize];
		top_n = -1;

	}
	
	~stack()
	{
		delete[] st;
	}
	
	bool isfull()
	{
		return top_n == maxtop_n;
	}
	
	bool isempty()
	{
		return top_n == -1;
	}
	
	bool push(const T & x)
	{
		if (isfull())
		{
			cout << "no memory" << endl;
			return false;
		}
		top_n++;
		st[top_n] = x;
		return true;
	}
	
	T pop()
	{
		if (isempty())
		{
			cerr << "no element" << endl;
		}
		T x;
		x = st[top_n];
		top_n--;
		return x;
	}
	
	T top()
	{
		return st[top_n];
	}

	void clear()
	{
		top_n = -1;
	}

	void output()
	{
		if (isempty())
		{
			cout << "栈已空" << endl;
		}
		else
		{
			for (int i = 0; i <= top_n; i++)
			{
				cout << st[i] << '\t';
			}
			cout << endl;
		}
	}

};


class Calculator 
{
public:
	string infix;
	string postfix;
	Calculator(string str);
	~Calculator() { poststack.clear(); };
	stack<double>poststack; 
	void infix_to_suffix();
	int isp(char opt_ch);
	int icp(char opt_ch);
	void cal_suffix();
	//double cal(double num1, double num2, char op);
	void Show_result();
	bool Get_operands(double &left_optnum, double &right_optnum);
	bool is_numelem(char ch);
	double returnnum(char * c, int n);
	float exchange_num(char num_ch);
	void  Do_Operator(char opt_ch);
};
Calculator::Calculator(string str)
{
	infix = str; 
}
//将中缀转换成后缀
void Calculator::infix_to_suffix()
{
	stack<char> OPTR;//一个用来存符号的栈
	OPTR.push('#');//开头用#标志
	char c;
	int i = 0;
	while ((OPTR.isempty() == false) && (i<infix.length()))
	{
		if (is_numelem(infix[i]))//判断中缀表达式中当前是否为数字
		{
			while (is_numelem(infix[i]))
			{
				postfix += infix[i];
				i++;
			}
			char c = '&';
			postfix += c;
		}
		else
		{   
			c = OPTR.top();
			if (icp(infix[i]) > isp(c))
			{
				OPTR.push(infix[i]);
				i++;
			}
			else if (icp(infix[i])<isp(c))
			{
				postfix += OPTR.pop();
			}
			else
			{
				if (OPTR.pop() == '(')
					i++;
			}
		}
	}
	while (OPTR.top() != '#')
		postfix += OPTR.pop();
	OPTR.clear();
}
void Calculator::cal_suffix()//计算后缀表达式
{
	infix_to_suffix();
	int i = 0;
	while (i<postfix.length())
	{
		if (postfix[i] == '+' || postfix[i] == '-' || postfix[i] == '*' || postfix[i] == '/')
		{
			Do_Operator(postfix[i]);
			i++;
			continue; //判断后缀表达式中当前是否为符号
		}
		else
		{
			if (is_numelem(postfix[i]))//需要将独立的数字联合成一个有意义的数
			{
				char c[11];
				int n = 0;
				while (postfix[i] != '&')//用&来区别每个数
				{
					c[n] = postfix[i];
					n++;
					i++;
				}
				poststack.push(returnnum(c, n));//将转化后的数压入栈中
				i++;
				n = 0;
			}
			else
			{
				cout << "Error..." << endl;
				exit(1);
			}
		}
	}
	Show_result();
}
//将左右操作数获取，并进行计算
bool Calculator::Get_operands(double &left_optnum, double &right_optnum)
{
	if (poststack.isempty())//栈空
	{
		cout << "Error: 栈已空！" << endl;
		exit(1);
		return false;
	}
	right_optnum = poststack.pop();//获取左操作数之后，栈空了
	if (poststack.isempty())//
	{
		cout << "Error: 在获取左操作数之后栈已空" << endl;
		exit(1);
		return false;
	}
	left_optnum = poststack.pop();
	return true;
}
double Calculator::returnnum(char * c, int n)
{
	int l = n;
	double num = 0;
	double m = 1;
	for (int i = l - 1; i >= 0; i--)
	{
		num += exchange_num(c[i])*m;
		m *= 10;
	}
	return num;
}

int Calculator::isp(char c)
{
	switch (c)
	{
	case'#':
		return 0; break;
	case'(':
		return 1; break;
	case'*':case'/':case'%':
		return 5; break;
	case'+':case'-':
		return 3; break;
	case')':
		return 6; break;
	}
}

int Calculator::icp(char c)
{
	switch (c)
	{
	case'#':
		return 0; break;
	case'(':
		return 6; break;
	case'*':case'/':case'%':
		return 4; break;
	case'+':case'-':
		return 2; break;
	case')':
		return 1; break;
	}
}

bool Calculator::is_numelem(char ch)
{
	if (48 <= ch && ch <= 57)
		return true;
	else
		return false;
}

float Calculator::exchange_num(char num_ch)
{
	return num_ch - 48;
}

void Calculator::Do_Operator(char cp)
{
	double left, right, value;
	if (Get_operands(left, right))
	{
		switch (cp)
		{
		case'+':
		{
			value = left + right;
			poststack.push(value);
			break;
		}
		case'-':
		{
			value = left - right;
			poststack.push(value);
			break;
		}
		case'*':
		{
			value = left * right;
			poststack.push(value);
			break;
		}
		case'/':
			if (right == 0)
			{
				cout << "Error: 分母为0" << endl;
				exit(1);
			}
			else
			{
				value = left / right;
				poststack.push(value);
			}
			break;
		}
	}
}

void Calculator::Show_result()
{
	cout << "Result： " << endl;
	cout << infix << " = " << poststack.top();
}

int main()
{
	char c[100];
	gets(c);
    //char * c="52+3*8+20";
	string str(c);
	Calculator jisuanqi(str);
	jisuanqi.cal_suffix();
}

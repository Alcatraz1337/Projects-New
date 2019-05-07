#include<string>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>


using namespace std;
template<class T>
class stack
{
private:
	int top_n;//ջ��
	int maxtop_n;//����ջ��ֵ
	T * st;//��ջԪ������
public:
	/*****����*****/
	stack(int maxstacksize = 20)
	{
		maxtop_n = maxstacksize - 1;
		st = new T[maxstacksize];
		top_n = -1;

	}
	~stack()
	{
		delete[] st;
	}
	/*****�ж�ջ�Ƿ�����*****/
	bool isfull()
	{
		return top_n == maxtop_n;
	}
	/*****�ж�ջ�Ƿ�Ϊ��*****/
	bool isempty()
	{
		return top_n == -1;
	}
	/*****��ջ�����Ԫ��*****/
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
	/*****ɾ��ջ��Ԫ��*****/
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
	/*****����ջ��Ԫ�ص�ֵ*****/
	T top()
	{
		return st[top_n];
	}
	/*****���ջ*****/
	void clear()
	{
		top_n = -1;
	}
	/*****���ջ*****/
	void output()
	{
		if (isempty())
		{
			cout << "ջ�ǿյ�" << endl;
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


class calculator
{
public:
    calculator();
    calculator(calculator &&) = default;
    calculator(const calculator &) = default;
    calculator &operator=(calculator &&) = default;
    calculator &operator=(const calculator &) = default;
    ~calculator();

    calculator(string infix);

    int isp(char oprt);
    int icp(char oprt);

    bool isNumeric(char c);

    void infix_to_postfix();
    void cal_postfix();
    void cal_operator(char oprt);
    bool getOprands(double &left, double &right);

private:
    string infixExp;
    string postfixExp;
    stack<double> poststack; //用于存后缀计算式
};

calculator::calculator(string infix)
{
    infixExp = infix;
}

calculator::~calculator()
{
}

int calculator::isp(char oprt){
    switch (oprt){
        case '#':
            return 0; break;
        case '(' :
            return 1; break;
        case '^':
            return 7; break;
        case '*': case'/':case'%':
            return 5; break;
        case '+' : case'-' :
            return 3; break;
        case ')':
            return 8; break;
        default:
            break;
    }
}

int calculator::icp(char oprt){
    switch(oprt){
        case '#':
            return 0; break;
        case '(':
            return 8; break;
        case '^':
            return 6; break;
        case '*' : case '/' : case '%':
            return 4; break;
        case '+' : case '-':
            return 2; break;
        case ')':
            return 1; break;
        default:
            break;
    }
}

bool calculator::isNumeric(char c){
    if( 48 <= c && c <= 57)
        return true;
    else
        return false;
}

bool calculator::getOprands(double &left, double &right）{
    if(poststack.isempty()){
        cout << "Error: Postfix Expression stack is empty!";
        exit(1);
        return false;
    }
    right = poststack.pop();
    if(poststack.isempty()){
        cout << "Error! Postfix expression is empty!";
        exit(1);
        return false;
    }
    left = poststack.pop();
    return true;
}

void calculator::cal_operator(char oprt){
    double left, right, value;
    if(getOperands(left, right)){
        
    }
}

void calculator::infix_to_postfix(){
    stack<char> oprt; // 创建一个栈 用来储存运算符
    oprt.push('#'); //第一个应该是#
    char c; // 用于转存字符
    int i = 0;
    while((oprt.isempty() == false) && (i < infixExp.length())){
        if(isNumeric(infixExp[i])){  // 判断infixExp中读取的是否为操作数，是则添加至postfix的末尾
                postfixExp += infixExp[i];
                i++; 
        } 
        else if(infixExp[i] == '(' || infixExp[i] == ')') {//infixExp中，当前符号是否为括号
            c = ' ';
            postfixExp += c; //在postfix后面加空格
            if(infixExp[i] == '(')
                oprt.push(infixExp[i++]);
            else{ // 当infixExp中，当前为')'，弹出栈中所有符号，如果为空或没遇见'('则出错
                if(oprt.isempty()){
                    cout << "Illigal expression! (Brackets not match!)";
                    exit(1);
                }
                while(oprt.top() != '('){
                    postfixExp += oprt.pop();
                    if(oprt.isempty()){
                        cout << "Illigal expression! (Brackets not match)";
                        exit(1);
                    }
                }
                oprt.pop(); // 不需要保留'('
                i++;
            }
        }     
        else{ //infixExp当前符号一定为运算符
            if(icp(infixExp[i]) > isp(oprt.top()))  //外大内小 入栈
                oprt.push(infixExp[i++]);
            else
            {
                while(icp(infixExp[i]) < isp(oprt.top()) && oprt.isempty() == false &&
                oprt.top() != '(') // 外小内大且栈不为空，弹出栈内不是'('的符号
                    postfixExp += oprt.pop();
                }
                oprt.push(infixExp[i]);
                i++;
            }

        }
    // 当infixExp已经读完，但是栈中仍有符号时，全部加入postfixExp的尾部，但是如果有'('则出错
    while(oprt.top() != '#'){
        if(oprt.top() == '('){
            cout << "Illigal expression! (Brackets not match!)";
            exit(1);
        }
        postfixExp += oprt.pop();
    } 
}

void calculator::cal_postfix(){
    infix_to_postfix();
    int i = 0;
    while (i < postfixExp.length()){ // 计算postfixExp中的项

    }
}

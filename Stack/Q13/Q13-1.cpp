#include <stack>
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

bool check(string s);

int main(){
    string brackets;
    bool isMatch;
    cout << "Input brackets: ";
    cin >> brackets;
    isMatch = check(brackets);
    if(isMatch)
        cout <<  "Match!";
    else
        cout << "Not Match!";

    return 0;
}

bool check(string str)
{
    stack<char> s;
    int len = str.length();
    int i = 0;
    for(; i < len; i++){
        char temp = str[i];
        switch(temp){
            case '(': case '[': case '{':
                s.push(str[i]);
                break;
            case ')':
                if(s.top() != '(')
                    return false;
                break;
            case ']':
                if(s.top() != '[')
                    return false;
                break;
            case '}':
                if(s.top() != '{')
                    return false;
                break;
        }
    }
    if(s.empty())
        return true;
    else
        return false;
}

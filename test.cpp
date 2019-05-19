#include <iostream>
#include <string>
using namespace std;
int main(){
    string a = "abcd";
    if(-1 < (int) a.length())
        cout << "true";
    else
    {
        cout << a.length();
        cout << "false";
    }
    return 0;
}
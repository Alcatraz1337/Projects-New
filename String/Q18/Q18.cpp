#include <string>
#include <iostream>

using namespace std;

int*getNext(string &pattern);
int kmp(string &t, string &p);

int* getNext(string &pattern){
    int *next = new int[pattern.length()];
    
    next[0] = -1;
    int k = -1;
    int j = 0;

    while(j < pattern.length() - 1){
        if(k == -1 || pattern[j] == pattern[k])
            next[++j] = ++k;
        else
            k = next[k];
    }
    return next;
}

int kmp(string &t, string &p){
    int *next = getNext(p);
    int i = 0; // 主串
    int j = 0; // 子串
    while(i <(int) t.length() && j <(int) p.length()){
        if(t[i] == p[j] || j == -1){ //j = -1时，移动i，j也要归零
            i++;
            j++;
        }
        else  
            j = next[j];

    }
    if(j == p.length())
        return i - j + 1;
    else
        return -1;
}

string reverseString(string &s){
    int len = s.length();
    char *rev = new char[len];
    int j = 0;
    for (int i = len - 1; i >= 0;)
        rev[j++] = s[i--];
    return rev;
}

int main(){
    string ptr = "str";
    string str = "substrsubstr";
    int strlen = str.length();
    int ptrlen = ptr.length();
    string ptrrev = reverseString(ptr);
    string strrev = reverseString(str);
    cout << "Match at: " << strlen + 1 - kmp(strrev, ptrrev) - ptrlen + 1 << endl;
    return 0;
}
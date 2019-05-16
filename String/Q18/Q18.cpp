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
    int i = 0;
    int j = 0;
    while(i < t.length() && j < p.length()){
        if(t[i] == p[j]){
            i++;
            j++;
        }
        else if(j != -1) //mismatch but not at the front of the p
            j = next[j];
        else //mismatch at the front of the p
            i++;
    }
    if(i == t.length() - 1 && j != p.length() - 1) // i reach the end of t, but haven't matched yet.
        return -1;
    else if (j == p.length() - 1)
        return i - p.length() + 1;
}

int main(){
    string ptr = "acacab";
    string str = "abccacacabcacbbba";
    cout << "Match at: " << kmp(str, ptr) << endl;
    return 0;
}
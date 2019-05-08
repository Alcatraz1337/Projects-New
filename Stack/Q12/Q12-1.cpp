#include <stack>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

void decShift(int n, int target, stack<int> &s);
void printStack(stack<int> &s);

int main(){
    stack<int> shift;
    int dec;
    int target;
    cout << "Enter number and the target radix." << endl;
    cin >> dec >> target;
    decShift(dec, target, shift);
    printStack(shift);
    return 0;
}

void decShift(int n, int target, stack<int> &s){
    if(n == 0)
        return;
    else{
        decShift(n / target, target, s);
        s.push(n % target);
    }
}

void printStack(stack<int> &s){
    while(!s.empty()){
        cout << s.top();
        s.pop();
    }
}

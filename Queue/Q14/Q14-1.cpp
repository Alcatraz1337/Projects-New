#include <queue>
#include <iostream>
#include <cstdlib>

using namespace std;

int main(){
    int n = 0;
    int temp = 0;
    queue<int> MyQueue[10];

    cout << "Enter number n: ";
    cin >> n;


    for(int i = 0; i < n; i++){
        cin >> temp;
        if(0 <= temp && temp <= 9){
            MyQueue[temp].push(temp);
        }
        else{
            cout << "Error: Illigal input!";
            exit(-1);
        }
    }

    for (int i = 0; i < 10; i++){
        while(!MyQueue[i].empty()){
            cout << MyQueue[i].front() << ' ';
            MyQueue[i].pop();
        }
    }

        return 0;
}
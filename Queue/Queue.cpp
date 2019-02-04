#include "Queue.h"

int *newArray(int length){
    int *array = new(length);
    return array;
}

int main()
{
    int len;
    cin >> len;
    
    int *q = newArray(len);
    
    int num;
    cin >> num;
    
    int i = 0, temp = 0;
    for(i; i < num; i++){
        cin >> temp;
        q[i] = temp;
    }
    
    int head = 0, tail = num;
    while(head < tail){
        cout << q[head];
        head++;
        
        q[tail] = q[head];
        tail++;
        head++;
    }
}

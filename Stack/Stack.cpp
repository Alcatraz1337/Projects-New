#include "Stack.h"

int getLength(char *a){
    int len;
    len = strlen(a);
    return len;
}

int getMid(int length){
    if(length % 2 == 0){
        return length / 2;
    }
    else{
        return length / 2 - 1;
    }
}

int getNext(int length){
    if(length % 2 == 0){
        return length / 2;
    }
    else{
        return length / 2 + 1;
    }
}

bool isPalindrome(int top){
    if(top == 0){
        return true;
    }
    else{
        return false;
    }
}

int main()
{
    char a[100];
    gets(a);

    int len = 0, next = 0, top = 0;
    len = getLength(a);
    top = getMid(len);
    next = getNext(len);
    for (; next < len; next++){
        if(a[next] != a[top])
            break;
        top--;
    }

    bool isPal = false;
    isPal = isPalindrome(top);
    
    if(isPal)
        cout << "Is Palindrome!" << endl;
    else
        cout << "Not Palindrome!" << endl;
    getchar();
    getchar();
    return 0;
}

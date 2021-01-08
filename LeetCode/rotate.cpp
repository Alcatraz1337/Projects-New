#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(){
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    
    reverse(v.begin(), v.end());
    for(int n:v)
        cout << n;
    return 0;
}

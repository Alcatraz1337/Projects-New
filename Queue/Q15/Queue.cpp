#include <iostream>

using namespace std;

class MyQueue{
    public:
        MyQueue(const int size);
        ~MyQueue();
        void push(int data);
        void pop();
        int head();
        int tail();
        bool isFull(); // tag
        bool isEmpty();

    private:
        bool tag; // 0 empty, 1 full
        int count;
        int size;
        int *array;
        int *front;
        int *rear;
};

MyQueue::MyQueue(const int size){
    array = new int[size];
    front = array;
    rear = front = array;
    tag = 0;
    this->size = size;
    count = 0;
}

MyQueue::~MyQueue(){
    delete array;
}

void MyQueue::push(int data){
    if(tag){ 
        cout << "Error: queue is already full!";
        exit(-1);
    }
    else{
        *rear = data;
        rear++;
        if()  //需要修改 逻辑问题
    }
}

void MyQueue::pop(){
    if(isEmpty()){
        cout << "Error: Queue is already empty!";
        exit(-1);
    }
    else{
        if(front == &array[size - 1])
            front = &array[0];
        front++;
    }
    count--;
}

int MyQueue::head(){
    return *front;
}

int MyQueue::tail(){
    return *rear;
}

int main(){
    MyQueue CircleQueue(8);
    int op = 0;
    int temp = 0;
    do{
        cout << "1: push / 2: pop / 3: check front / 4: check rear / 0: exit\n";
        cin >> op;
        switch(op){
            case 1:
                cout << "Enter enqueue number: ";
                cin >> temp;
                CircleQueue.push(temp);
                break;
            case 2:
                CircleQueue.pop();
                break;
            case 3:
                if(CircleQueue.isEmpty()){
                    cout << "Error: Queue is empty!";
                    break;
                }
                cout << CircleQueue.head() << endl;
                break;
            case 4:
                if(CircleQueue.isEmpty()){
                    cout << "Error: Queue is empty!";
                    break;
                }
                cout << CircleQueue.tail() << endl;
                break;
            default:
                break;
        }
    } while(op);

    return 0;
}

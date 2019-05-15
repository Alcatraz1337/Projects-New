#include <iostream>

using namespace std;

class MyQueue{
    public:
        MyQueue(const int size);
        ~MyQueue();
        void push(int data);
        void pop();
        int head();
        void checkQueue();
        bool isFull(); // tag
        bool isEmpty();

    private:
        bool tag; // 0 empty, 1 full
        int size;
        int *array;
        int front;
        int rear;
};

MyQueue::MyQueue(const int size){
    array = new int[size];
    for (int i = 0; i < size; i++){
        array[i] = 0;
    }
        rear = front = 0;
    tag = 0;
    this->size = size;
}

MyQueue::~MyQueue(){
    delete array;
}

bool MyQueue::isEmpty(){
    return (front == rear && tag == 0);
}

bool MyQueue::isFull(){
    return (front == rear && tag == 1);
}

void MyQueue::push(int data){
    if(isFull()){
        cout << "Error: queue is already full!" << endl;
        return;
    }
    array[rear] = data;
    rear = (rear + 1) % size;
    if(rear == front)  //需要修改 逻辑问题
        tag = 1;
}

void MyQueue::pop(){
    if(isEmpty()){
        cout << "Error: Queue is already empty!" << endl;
        return;
    }
    front = (front + 1) % size;
    if(rear == front)
        tag = 0;
}

void MyQueue::checkQueue(){
    for(int i = 0; i < size; i++){
        cout << array[i] << ' ';
    }
    cout << endl;
    cout << "Front pos: " << front << "\n Rear pos: " << rear << endl;
}

int MyQueue::head(){
    return array[front];
}

int main(){
    MyQueue CircleQueue(8);
    int op = 0;
    int temp = 0;
    do{
        cout << "1: push / 2: pop / 3: check front /4: check queue/ 0: exit\n";
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
                CircleQueue.checkQueue();
            default:
                break;
        }
    } while(op);

    return 0;
}

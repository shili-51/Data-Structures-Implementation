Implement a Queue using a circular buffer (fixed-size array) — no linked list allowed.

Use front and rear indices with mod arithmetic
Support enqueue, dequeue, peek, isFull, isEmpty

enqueue, dequeue, peek, isFull, isEmpty = O(1)

#include <iostream>
#include <stdexcept>
using namespace std;

class Queue{
    int rear;
    int front;
    int* arr;
    int size;
    int capacity;
    
    public:
    Queue(int n){
        size = 0;
        capacity = n;
        front = 0;
        rear = -1;
        arr = new int[capacity];
    }
    ~Queue(){
        delete[] arr;
    }
    
    void enqueue(int val){
        if(isFull()) throw overflow_error("queue is full");
        rear = (rear + 1) % capacity;
        arr[rear] = val;
        size++;
    }
    
    int dequeue(){
        if(isEmpty()) throw out_of_range("queue is empty");
        int val = arr[front];
        front = (front + 1) % capacity;
        size--;
        return val;
    }
    
    int peek(){
        if(isEmpty()) throw out_of_range("queue is empty");
        return arr[front];
    }
    
    bool isFull(){
        return (size == capacity);
    }
    
    bool isEmpty(){
        return (size == 0);
    }
    
    void display(){
        if(isEmpty()){
            cout<<"Queue is Empty"<<endl;
            return;
        }
        
        for(int i = 0; i < size; i++){
            cout<<"Element in queue : "<<arr[(front + i) % capacity]<<endl;
        }
    }
    
};

int main(){
    Queue q(5);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    q.enqueue(5);
    q.display();
    int res = q.dequeue();
    cout<<res<<endl;
    q.display();
    int val = q.peek();
    cout<<val<<endl;
}


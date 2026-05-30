#include <iostream>
#include <stdexcept>
using namespace std;

class Deque{
    int* arr;
    int front;
    int rear;
    int size;
    int capacity;
    
    public:
    Deque(int n){
        capacity = n;
        size = 0;
        front = 0;
        rear = -1;
        arr = new int[capacity];
    }
    
    ~Deque(){
        delete[] arr;
    }
    
    void insertFront(int val){
        if(isFull()) throw overflow_error("Queue is full");
        if(isEmpty()){
            front = 0;
            rear = 0;
        }
        else{
            front = (front - 1 + capacity) % capacity;
        }
        arr[front] = val;
        size++;
    }
    
    void insertBack(int val){
        if(isFull()) throw overflow_error("Queue is full");
        if(isEmpty()){
            front = 0;
            rear = 0;
        }
        else{
            rear = (rear + 1) % capacity;
        }
        arr[rear] = val;
        size++;
    }
    
    int deleteFront(){
        if(isEmpty()) throw runtime_error("Deque is empty");
        int val = arr[front];
        if(size == 1){
            front = 0;
            rear = -1;
        }
        else front = (front + 1) % capacity;
        size--;
        return val;
    }
    
    int deleteBack(){
        if(isEmpty()) throw runtime_error("Deque is empty");
        int val = arr[rear];
        if(size == 1){
            front = 0;
            rear = -1;
        }
        else rear = (rear - 1 + capacity) % capacity;
        size--;
        return val;
    }
    
    int getFront(){
        if(isEmpty()) throw runtime_error("Deque is empty");
        return arr[front];
    }
    
    int getRear(){
        if(isEmpty()) throw runtime_error("Deque is empty");
        return arr[rear];
    }
    
    bool isFull() const{
        return size == capacity;
    }
    
    bool isEmpty() const{
        return size == 0;
    }
    
    void display(){
        if(isEmpty()){
            throw runtime_error("Deque is empty");
            return;
        }
        
        for(int i = 0; i < size; i++){
            cout<<"Deque Element : "<< arr[(front + i) % capacity]<<endl;
        }
    }
    
};


int main(){
    
    // Deque
    Deque dq(5);
    dq.insertFront(5);
    dq.insertBack(10);
    dq.insertFront(4);
    dq.insertBack(8);
    dq.insertFront(2);
    
    dq.display();
    int val = dq.deleteFront();
    cout<<val<<endl;
    val = dq.deleteBack();
    cout<<val<<endl;
}


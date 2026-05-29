Problem Statement - "Can you implement two stacks in a single fixed-size array efficiently?"


#include<iostream>
#include<stdexcept>
using namespace std;

template<typename T>
class dynamicArray{
    private:
    T* arr;
    int size;
    int cap;
    
    public:
    dynamicArray(){
        size = 0;
        cap = 4;
        arr = new T[cap];
    }
    
    ~dynamicArray(){
        delete[] arr;
    }
    
    void push_back(T val){
        if(size >= cap){
            cap = 2*cap;
            T* newArr = new T[cap];
            int i = 0;
            while(i < size){
                newArr[i] = arr[i];
                i++;
            }
            newArr[i] = val;
            delete[] arr;
            arr = newArr;
        }
        else{
            arr[size] = val;
        }
        size++;
    }
    
    void pop_back(){
        if(size == 0) throw out_of_range("Array is empty");
        size--;
    }
    
    T back(){
        if(size == 0) throw out_of_range("Array is empty");
        return arr[size-1];
    }
    
    int getSize() const{
        return size;
    }
    
    bool isEmpty() const{
        return size == 0;
    }
    
};

template<typename T>
class Stack{
    private:
    dynamicArray<T> da;
    
    public:
    
    T peek(){
        if(da.getSize() == 0) throw out_of_range("Stack is empty");
        return da.back();
    }
    
    void push(T val){
        da.push_back(val);
    }
    
    T pop(){
        if(da.getSize() == 0) throw out_of_range("Stack is empty");
        T val = da.back();
        da.pop_back();
        return val;
    }
    
    bool isEmpty(){
        return da.isEmpty();
    }
    
    int getSize() const{
        return da.getSize();
    }
    
};

class implementTwoStacks{
    private:
    int* arr;
    int length;
    int top1;
    int top2;
    
    public: 
    implementTwoStacks(int n){
        length = n;
        top1 = -1;
        top2 = length;
        arr = new int[length];
    }
    
    ~implementTwoStacks(){
        delete[] arr;
    }
    
    void push1(int val){
        if(top1 >= top2){
            throw out_of_range("Stack Overflow");
        }
        arr[++top1] = val;
    }
    
    void push2(int val){
        if(top2 <= top1){
            throw out_of_range("Stack Overflow");
        }
        arr[--top2] = val;
    }
    
    int pop1(){
        if(top1 == -1){
            throw out_of_range("Stack Overflow");
        }
        int val = arr[top1];
        top1--;
        return val;
    }
    
     int pop2(){
        if(top2 == length){
            throw out_of_range("Stack Overflow");
        }
        int val = arr[top2];
        top2++;
        return val;
    }
    
    int peek1(){
        if(top1 == -1){
            throw out_of_range("Stack Overflow");
        }
        return arr[top1];
    }
    
    int peek2(){
        if(top2 == length){
            throw out_of_range("Stack Overflow");
        }
        return arr[top2];
    }
    
    bool isEmpty1(){
        return top1==-1;
    }
    
    bool isEmpty2(){
        return top2==length;
    }
    
    
};

int main(){
    
    // int arr[11] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    implementTwoStacks ts(11);
    ts.push1(1);  ts.push1(2);  ts.push1(3);
    ts.push2(11); ts.push2(10); ts.push2(9);

    cout << ts.peek1() << endl;   // 3
    cout << ts.peek2() << endl;   // 9
    cout << ts.pop1()  << endl;   // 3
    cout << ts.pop2()  << endl;   // 9
}

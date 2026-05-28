Problem Statement - Implement a Stack using your own dynamic array (not std::vector or std::stack).

Support push, pop, peek, isEmpty, size
pop and peek on empty stack should throw
Then implement: given a string of brackets, return true if balanced
Then implement: evaluate a postfix expression using the stack


// Implementation - 
#include<iostream>
#include<stdexcept>
using namespace std;

template<typename T>
class dynamicArray{
    private:
    T *arr;
    int size;
    int capacity;
    
    public:
    dynamicArray(){
        size = 0;
        capacity = 4;
        arr = new T[capacity];
    }
    
    ~dynamicArray(){
        delete[] arr;
    }
    
    void push_back(T val){
        if(size < capacity){
            arr[size] = val;
            size++;
        }else{
            capacity = 2*capacity;
            T* newArr = new T[capacity];
            int i = 0;
            while(i < size){
                newArr[i] = arr[i];
                i++;
            }
            newArr[i] = val;
            size++;
            delete[] arr;
            arr = newArr;
        }
    }
    
    void pop_back(){
        if(size == 0) throw out_of_range("Array is empty");
        size--;
    }
    
    int back() const{
        if(size == 0) throw out_of_range("Array is empty");
        return arr[size - 1];
    }
    
    int getSize() const {
        return size;
    }
    
    bool isEmpty() const{
        if(size == 0) return true;
        return false;
    }
    
};

template<typename T>
class Stack{
    private:
    dynamicArray<T> st;
    
    public: 
    void push(T val){
        st.push_back(val);
    }
    
    T pop(){
        if(st.getSize() == 0) throw out_of_range("Stack is empty");
        T x = st.back();
        st.pop_back();
        return x;
    }
    
    T peek(){
        if(st.getSize() == 0) throw out_of_range("Stack is empty");
        return st.back();
    }
    
    bool isEmpty(){
        return st.isEmpty();
    }
    
    int getSize() const{
        return st.getSize();
    }
    
};

bool balance(char a, char b){
    if((a == '(' && b == ')') || (a == '{' && b == '}') || (a == '[' && b == ']')) return true;
    return false;
}

bool isBalanced(const char* s){
    int i = 0;
    Stack<char> st;
    while(s[i] != '\0'){
        if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
            st.push(s[i]);
        }else{
            if(!st.isEmpty()){
                char temp = st.peek();
                if(!balance(temp,s[i])) return false;
                st.pop();
            }
            else return false;
        }
        i++;
    }
    return st.isEmpty();
}

int main(){
    //balance paranthesis
    bool res = isBalanced("{})(");
    cout<<res;
    
}

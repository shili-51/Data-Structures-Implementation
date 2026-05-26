Problem Statement - Build a MyString class that wraps a char array — no std::string allowed anywhere.

Store characters in a char* with a length field
Implement length(), append(str), substring(start, len), find(char)
Overload + for concatenation and == for comparison
Implement reverse() in-place

Implementation - 
#include<iostream>
using namespace std;

class MyString{
    private:
    int length;
    char *arr;
    
    int strLen(const char* s) const{
        int len = 0;
        while(s[len] != '\0') len++;
        return len;
    }
    
    public : 
    MyString(){
        length = 0;
        arr = new char[1];
        arr[0] = '\0';
    }
    
    ~MyString(){
        delete []arr;
    }
    
    MyString(const char* s){
        int len = strLen(s);
        length = len;
        arr = new char[length + 1];
        int i = 0;
        while(i < len){
            arr[i] = s[i];
            i++;
        }
        arr[i] = '\0';
    }
    
    int getLength() const{
        return length;
    }
    
    
    void append(const char* s){
        int sLen = strLen(s);
        int newLen = length + sLen;
        char* newArr = new char[newLen + 1];
        int i = 0;
        while(i < length){
            newArr[i] = arr[i];
            i++;
        }
        while(i < newLen){
            newArr[i] = s[i - length];
            i++;
        }
        newArr[newLen] = '\0';
        delete[] arr;
        arr = newArr;
        length = newLen;
    }
    
    char* substring(int start, int len){
        char* newArr = new char [len + 1];
        for(int i = 0; i < len; i++){
            newArr[i] = arr[start + i];
        }
        newArr[len] = '\0';
        return newArr;
    }
    
    char find(char a){
        for(int i = 0; i < length; i++){
            if(arr[i] == a){
                return arr[i];
            }
        }
        return '\0';
    }
    
    MyString operator+(const MyString& other) const{
        MyString res;
        res.length = length + other.length;
        delete[] res.arr;
        res.arr = new char[res.length + 1];
        
        int i = 0;
        while(i < length){
            res.arr[i] = arr[i];
            i++;
        }
        while(i < res.length){
            res.arr[i] = other.arr[i-length];
            i++;
        }
        res.arr[i] = '\0';
        return res;
    }
    
    bool operator==(const MyString& other) const{
        if(length != other.length) return false;
        int i = 0;
        while(i < length){
            if(arr[i] != other.arr[i]) return false;
            i++;
        }
        return true;
    }
    
    void reverse(){
        int left = 0;
        int right = length - 1;
        while(left < right){
            char temp = arr[right];
            arr[right] = arr[left];
            arr[left] = temp;
            left++;
            right--;
        }
    }
    
    void print() const{
        cout<<arr<<endl;
    }
    
};

int main(){
    MyString s1("Hello");
    s1.print();
    
    s1.append(" World");
    s1.print();
    
    MyString s2("Hi");
    MyString s3(" Shilpy");
    MyString s4 = s2 + s3;  // This calls copy constructor, not assignment operator.
                         // s2 + s3 creates a temp MyString object, and s4 is 
                         // initialized from it using copy constructor at declaration time.
                         // Since we haven't implemented copy constructor, default 
                         // shallow copy is used — but it works here because the temp 
                         // object's arr is copied to s4.arr before temp is destroyed.
                         // However declaring s4 first and then doing s4 = s2 + s3 
                         // would use assignment operator which we haven't implemented,
                         // causing shallow copy bug and bogus values.
    s4.print();
    
    MyString s5("Hello Word");
    cout<<(s4 == s5 ? "Equal" : "Not Equal")<<endl;
    
    char* sub = s1.substring(2, 2);
    cout<<sub<<endl;
    delete[] sub;
    
    cout<<s1.find('W')<<endl;
    
    s1.reverse();
    s1.print();
    
    cout<<s1.getLength()<<endl;
    
}


"Why is repeated string concatenation in a loop O(n²)? How would you fix it?"
"Each + allocates a new buffer and copies all previous content, so N concatenations copy 1+2+...+N = O(n²) characters total. 
Fix it with a StringBuilder pattern — pre-allocate a buffer with capacity doubling, append in-place, and build the final string once at the end — giving O(n) amortized."

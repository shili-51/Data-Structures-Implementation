Problem Statement :
Implement a generic dynamic array (like std::vector) from scratch without using any STL containers.
Start with capacity 4, double it when full
Support push_back, pop_back, operator[], size, capacity
Handle index-out-of-bounds with an exception
Implement a resize(n) method and a clear() method

#include <iostream>
#include <stdexcept>
using namespace std;

class dynamicArray {
    int *arr;
    int sz;
    int cap;

public:
    dynamicArray() {
        sz = 0;
        cap = 4;
        arr = new int[cap];
    }

    ~dynamicArray() {
        delete[] arr;
    }

    void push_back(int x) {
        if (sz == cap) {
            cap *= 2;
            int *newArr = new int[cap];
            for (int i = 0; i < sz; i++)
                newArr[i] = arr[i];
            delete[] arr;
            arr = newArr;
        }
        arr[sz++] = x;
    }

    int pop_back() {
        if (sz == 0)
            throw std::out_of_range("Array is empty");
        return arr[--sz];
    }

    int& operator[](int index) {
        if (index < 0 || index >= sz)
            throw std::out_of_range("Index out of range");
        return arr[index];
    }

    int getSize() const {
        return sz;
    }

    int getCapacity() const {
        return cap;
    }

    void resize(int n) {
        if (n > cap) {
            int newCap = cap;
            while (newCap < n)
                newCap *= 2;
            int *newArr = new int[newCap];
            for (int i = 0; i < sz; i++)
                newArr[i] = arr[i];
            for (int i = sz; i < n; i++)
                newArr[i] = 0; // default initialize new slots
            delete[] arr;
            arr = newArr;
            cap = newCap;
        }
        sz = n;
    }

    void clear() {
        sz = 0;
    }
};

int main() {
    // Example usage
    dynamicArray da;
    da.push_back(1);
    da.push_back(2);
    da.push_back(3);
    da.push_back(4);
    da.push_back(5);
    cout << "Size: " << da.getSize() << ", Capacity: " << da.getCapacity() << endl;
    da.resize(10);
    cout << "After resize, Size: " << da.getSize() << ", Capacity: " << da.getCapacity() << endl;
    da.clear();
    cout << "After clear, Size: " << da.getSize() << endl;
}


Interviewer Follow up = What's the amortized time complexity of push_back? Why doubling and not +1 each time?
Ans : The amortized time complexity of push_back is 
O(1)

Why double the capacity instead of increasing by 1? 
If you increase by 1, each push_back would need to copy all elements—making it 
O(n) every time! Doubling keeps most insertions fast, and only occasionally does a big copy.

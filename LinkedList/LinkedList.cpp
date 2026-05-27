Problem Statement - Implement a doubly linked list from scratch with full forward and backward traversal.

Node struct holds data, *prev, *next — no smart pointers
Implement insertFront, insertBack, insertAt(pos), deleteFront, deleteBack, deleteAt(pos)
Implement reverse() by rewiring pointers, not swapping data
Detect a cycle using Floyd's two-pointer algorithm



#include<iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int val) {
        data = val;
        prev = nullptr;
        next = nullptr;
    }
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() {
        head = nullptr;
    }

    ~LinkedList() {
        Node* curr = head;
        while(curr != nullptr) {
            Node* nex = curr->next;
            delete curr;           // ✅ delete not delete[]
            curr = nex;
        }
    }

    void insertFront(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        newNode->prev = nullptr;
        if(head != nullptr)
            head->prev = newNode;  // ✅ guard against empty list
        head = newNode;
    }

    void insertBack(int value) {
        Node* newNode = new Node(value);
        if(head == nullptr) {      // ✅ empty list case
            head = newNode;
            return;
        }
        Node* curr = head;
        while(curr->next != nullptr)
            curr = curr->next;
        curr->next = newNode;
        newNode->prev = curr;
    }

    void insertAtPos(int pos, int val) {
        if(pos == 0) {
            insertFront(val);
            return;
        }
        int len = 0;
        Node* curr = head;
        while(curr != nullptr && len < pos) {
            curr = curr->next;
            len++;
        }
        if(curr == nullptr) {      // ✅ pos out of range
            insertBack(val);
            return;
        }
        Node* newNode = new Node(val);
        Node* prevNode = curr->prev;
        newNode->prev = prevNode;
        newNode->next = curr;
        prevNode->next = newNode;
        curr->prev = newNode;
    }

    void deleteFront() {           // ✅ void, no return
        if(head == nullptr) return;
        Node* temp = head;
        head = head->next;
        if(head != nullptr)
            head->prev = nullptr;
        delete temp;               // ✅ delete not delete[]
    }

    void deleteBack() {            // ✅ no value parameter
        if(head == nullptr) return;
        if(head->next == nullptr) {  // only one node
            delete head;
            head = nullptr;
            return;
        }
        Node* curr = head;
        while(curr->next != nullptr)
            curr = curr->next;
        Node* prevNode = curr->prev;
        prevNode->next = nullptr;
        delete curr;               // ✅ delete not delete[]
    }

    void deleteAtPos(int pos) {
        if(head == nullptr) return;
        if(pos == 0) {
            deleteFront();
            return;
        }
        int len = 0;
        Node* curr = head;
        while(curr != nullptr && len < pos) {
            curr = curr->next;
            len++;
        }
        if(curr == nullptr) return;  // ✅ pos out of range
        Node* prevNode = curr->prev;
        Node* nexNode = curr->next;
        if(prevNode != nullptr) prevNode->next = nexNode;
        if(nexNode != nullptr) nexNode->prev = prevNode;
        delete curr;               // ✅ delete not delete[]
    }

    void reverse() {
        Node* curr = head;
        Node* temp = nullptr;
        while(curr != nullptr) {   // ✅ process all nodes including last
            temp = curr->prev;     // swap prev and next
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;     // ✅ move forward via prev (which is old next)
        }
        if(temp != nullptr)
            head = temp->prev;     // ✅ update head to last node
    }

    // ✅ Floyd's cycle detection — was completely missing
    bool hasCycle() {
        Node* slow = head;
        Node* fast = head;
        while(fast != nullptr && fast->next != nullptr) {
            slow = slow->next;          // moves 1 step
            fast = fast->next->next;    // moves 2 steps
            if(slow == fast) return true;  // they met — cycle exists
        }
        return false;
    }

    void printForward() const {
        Node* curr = head;
        while(curr != nullptr) {
            cout << curr->data << " <-> ";
            curr = curr->next;
        }
        cout << "NULL" << endl;
    }

    void printBackward() const {
        Node* curr = head;
        if(curr == nullptr) return;
        while(curr->next != nullptr)
            curr = curr->next;
        while(curr != nullptr) {
            cout << curr->data << " <-> ";
            curr = curr->prev;
        }
        cout << "NULL" << endl;
    }
};

int main() {
    LinkedList list;

    list.insertBack(1);
    list.insertBack(2);
    list.insertBack(3);
    list.insertFront(0);
    list.printForward();    // 0 <-> 1 <-> 2 <-> 3 <-> NULL

    list.insertAtPos(2, 99);
    list.printForward();    // 0 <-> 1 <-> 99 <-> 2 <-> 3 <-> NULL

    list.deleteFront();
    list.printForward();    // 1 <-> 99 <-> 2 <-> 3 <-> NULL

    list.deleteBack();
    list.printForward();    // 1 <-> 99 <-> 2 <-> NULL

    list.deleteAtPos(1);
    list.printForward();    // 1 <-> 2 <-> NULL

    list.reverse();
    list.printForward();    // 2 <-> 1 <-> NULL

    cout << (list.hasCycle() ? "Cycle detected" : "No cycle") << endl;  // No cycle
}



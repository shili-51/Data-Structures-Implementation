Problem Statement - Implementation of queue using 2 stacks

Time Complexity : 
enqueue	O(1)
dequeue	O(1) amortized
peek	O(1) amortized
isEmpty	O(1)

  
class Queue{
    private: 
    stack<int>s1;
    stack<int>s2;
    
    void transfer(){
         while(!s1.empty()){
                s2.push(s1.top());
                s1.pop();
            }
    }
    
    public: 
    void enqueue(int val){
        s1.push(val);
    }
    
    int dequeue(){
        if(isEmpty()) throw runtime_error("Queue is empty");
        if(s2.empty()){
            transfer();
        }
        int val = s2.top();
        s2.pop();
        return val;
    }
    
    int peek(){
        if(isEmpty()) throw runtime_error("Queue is empty");
        if(s2.empty()){
            transfer();
        }
        return s2.top();
    }
    
    bool isEmpty(){
        return s1.empty() && s2.empty();
    }
};

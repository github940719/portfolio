#include <iostream>
#include <stdexcept>
using namespace std;


template <typename T>
class myStack {
private:
    int maxSize = 50 ;
    int* arr = nullptr ;
    int top = -1 ;

public:
    myStack(int maxSize = 50) : maxSize(maxSize) {
        if (arr) {
            delete [] arr ;
        }
        arr = new int[maxSize] ;
    } 

    bool isFull() {
        return (top == maxSize - 1) ;
    }


    bool isEmpty() {
        return (top == -1) ;
    }

    void push(T element) {
        if (isFull()) {
            throw runtime_error("Stack is full");
        }
        arr[++top] = element ;
    }

    T peek() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
        return arr[top] ;
    }

    T pop() {
        if (isEmpty()) {
            throw runtime_error("Stack is empty");
        }
        return arr[top--] ;
    }
} ;

template <typename T>
class myQueue {
private:
    int maxSize ;
    int* arr = nullptr ;
    int front = 0, rear = 0 ;

public:
    myQueue(int maxSize = 50) : maxSize(maxSize + 1) {
        if (arr) {
            delete [] arr ;
        }
        arr = new int[maxSize] ;  // maxSize = capacity + 1
    }

    bool isEmpty() {
        return (front == rear) ;
    }

    bool isFull() {
        return ((rear + 1) % maxSize == front) ;
    }

    void push(T element) {
        if (isFull()) {
            throw runtime_error("queue is full") ;
        }
        rear = (rear + 1) % maxSize ;
        arr[rear] = element ;
    }

    T peek() {
        if (isEmpty()) {
            throw runtime_error("queue is empty") ;
        }
        return arr[rear] ;
    }

    T pop() {
        if (isEmpty()) {
            throw runtime_error("queue is empty") ;
        }
        front = (front + 1) % maxSize ;
        return arr[front] ;
    }
} ;



int main() {
    myQueue<int> queue(1) ;
    queue.push(10) ;
    queue.push(20) ;
    cout << queue.peek() << endl ;
    queue.pop() ;
    queue.pop() ;
    return 0 ;
}